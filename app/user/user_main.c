#include "user_main.h"
#include "uart.h"

static const partition_item_t at_partition_table[] = {
    { SYSTEM_PARTITION_BOOTLOADER, 						0x0, 												0x1000},	//boot占一个扇区
    { SYSTEM_PARTITION_OTA_1,   						0x1000, 											SYSTEM_PARTITION_OTA_SIZE},
    { SYSTEM_PARTITION_OTA_2,   						SYSTEM_PARTITION_OTA_2_ADDR, 						SYSTEM_PARTITION_OTA_SIZE},
    { SYSTEM_PARTITION_RF_CAL,  						SYSTEM_PARTITION_RF_CAL_ADDR, 						0x1000},    //用于系统自动保存校正后的RF参数（4KB）
    { SYSTEM_PARTITION_PHY_DATA, 						SYSTEM_PARTITION_PHY_DATA_ADDR, 					0x1000},    //默认RF参数区（4KB）
    { SYSTEM_PARTITION_SYSTEM_PARAMETER, 				SYSTEM_PARTITION_SYSTEM_PARAMETER_ADDR, 			0x3000},    //系统参数区（12KB）
    { SYSTEM_PARTITION_CUSTOMER_PRIV_PARAM,             SYSTEM_PARTITION_CUSTOMER_PRIV_PARAM_ADDR,          0x1000},    //用户参数，可放在任意未被占用的Flash
};

void ICACHE_FLASH_ATTR user_pre_init(void)
{
    if(!system_partition_table_regist(at_partition_table, sizeof(at_partition_table)/sizeof(at_partition_table[0]),SPI_FLASH_SIZE_MAP)) {
		os_printf("system_partition_table_regist fail\r\n");
		while(1);
	}
}

struct softap_config temp_AP_config;

struct espconn AP_ptrespconn;	//UDP imformation struct

/*
 * UDP接收事件
 */
void ICACHE_FLASH_ATTR
udp_event_recv(void *arg, char *pusrdata, unsigned short length)
{
	uart0_tx_buffer(pusrdata,length);
    return;
}



void user_init(void)
{
    system_set_os_print (0);	//0关闭系统打印
	system_init_done_cb(system_init_done);	//注册系统初始化完成回调函数
}

void ICACHE_FLASH_ATTR system_init_done()
{
	os_printf("System init done\r\n");
	//UART0 IO3 RX,IO1 TX,UART1 IO2 TX,IO8 RX
	uart_init(1000000, BIT_RATE_115200);	//串口初始化,其中包含os_install_putc1函数
    //os_install_putc1((void *)uart1_write_char);     //将打印端口改为uart1
	wifi_set_opmode(0x02);		//设置WiFi工作模式为AP并保存到Flash
	AP_UDP_Init();	//用于在任何时刻都可对ESP8266进行设置
}

void ICACHE_FLASH_ATTR udp_init(struct espconn* p_ptrespconn,int local_port)
{
	//初始化UDP
	p_ptrespconn->type = ESPCONN_UDP;
	p_ptrespconn->proto.udp = (esp_udp *)os_zalloc(sizeof(esp_udp));
	p_ptrespconn->proto.udp->local_port = local_port;
	espconn_regist_recvcb(p_ptrespconn, udp_event_recv);
	espconn_create(p_ptrespconn);
	os_printf("UDP init done\r\n");
}

void ICACHE_FLASH_ATTR
AP_UDP_Init()
{
	wifi_softap_get_config(&temp_AP_config);	//查询AP接口保存在Flash中的配置
	if(temp_AP_config.ssid[0]!='B')
	{
		os_memset(temp_AP_config.ssid, 0, 32);
		os_memset(temp_AP_config.password, 0, 64);
		os_memcpy(temp_AP_config.ssid, "BBA's_AP", 8);
		os_memcpy(temp_AP_config.password, "123123123", 9);
		temp_AP_config.authmode = AUTH_WPA_WPA2_PSK;
		temp_AP_config.ssid_len = 8;// or its actual length
		temp_AP_config.max_connection = 4; // how many stations can connect to ESP8266 softAP at most.
		wifi_softap_set_config(&temp_AP_config);
		os_printf("AP Set Sucess!");
	}
	udp_init(&AP_ptrespconn,1025);	//初始化UDP
}
