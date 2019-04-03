#ifndef USER_MAIN_H__
#define USER_MAIN_H__

#include "osapi.h"
#include "eagle_soc.h"
#include "mem.h"	//�ڴ�������
#include "user_interface.h"	//
#include "espconn.h"		//����ӿ����

#if (SPI_FLASH_SIZE_MAP == 0) 
#error "The flash map is not supported"
#elif (SPI_FLASH_SIZE_MAP == 1)
#define SYSTEM_PARTITION_OTA_SIZE
#elif (SPI_FLASH_SIZE_MAP == 2)
#define SYSTEM_PARTITION_OTA_SIZE							0x6A000		//��user1,user2�Ĵ�С
#define SYSTEM_PARTITION_OTA_2_ADDR							0x81000
#define SYSTEM_PARTITION_RF_CAL_ADDR						0xfb000
#define SYSTEM_PARTITION_PHY_DATA_ADDR						0xfc000
#define SYSTEM_PARTITION_SYSTEM_PARAMETER_ADDR				0xfd000
#define SYSTEM_PARTITION_CUSTOMER_PRIV_PARAM_ADDR           0x7c000
#elif (SPI_FLASH_SIZE_MAP == 3)
#define SYSTEM_PARTITION_OTA_SIZE							0x6A000
#define SYSTEM_PARTITION_OTA_2_ADDR							0x81000
#define SYSTEM_PARTITION_RF_CAL_ADDR						0x1fb000
#define SYSTEM_PARTITION_PHY_DATA_ADDR						0x1fc000
#define SYSTEM_PARTITION_SYSTEM_PARAMETER_ADDR				0x1fd000
#define SYSTEM_PARTITION_CUSTOMER_PRIV_PARAM_ADDR           0x7c000
#elif (SPI_FLASH_SIZE_MAP == 4)
#define SYSTEM_PARTITION_OTA_SIZE							0x6A000     //424K		//��user1,user2�Ĵ�С��424kb��
#define SYSTEM_PARTITION_OTA_2_ADDR							0x81000		//user2��ʼ��ַ��ǰ��һ��������Ԥ���ģ���С����boot
#define SYSTEM_PARTITION_RF_CAL_ADDR						0x3fb000	//����ϵͳ�Զ�����У�����RF������4KB��
#define SYSTEM_PARTITION_PHY_DATA_ADDR						0x3fc000	//Ĭ��RF��������4KB��
#define SYSTEM_PARTITION_SYSTEM_PARAMETER_ADDR				0x3fd000	//ϵͳ��������12KB��
#define SYSTEM_PARTITION_CUSTOMER_PRIV_PARAM_ADDR           0x7c000		//�û��������ɷ�������δ��ռ�õ�Flash
#elif (SPI_FLASH_SIZE_MAP == 5)
#define SYSTEM_PARTITION_OTA_SIZE							0x6A000
#define SYSTEM_PARTITION_OTA_2_ADDR							0x101000
#define SYSTEM_PARTITION_RF_CAL_ADDR						0x1fb000
#define SYSTEM_PARTITION_PHY_DATA_ADDR						0x1fc000
#define SYSTEM_PARTITION_SYSTEM_PARAMETER_ADDR				0x1fd000
#define SYSTEM_PARTITION_CUSTOMER_PRIV_PARAM_ADDR           0xfc000
#elif (SPI_FLASH_SIZE_MAP == 6)
#define SYSTEM_PARTITION_OTA_SIZE							0x6A000
#define SYSTEM_PARTITION_OTA_2_ADDR							0x101000
#define SYSTEM_PARTITION_RF_CAL_ADDR						0x3fb000
#define SYSTEM_PARTITION_PHY_DATA_ADDR						0x3fc000
#define SYSTEM_PARTITION_SYSTEM_PARAMETER_ADDR				0x3fd000
#define SYSTEM_PARTITION_CUSTOMER_PRIV_PARAM_ADDR           0xfc000
#else
#error "The flash map is not supported"
#endif

#define SYSTEM_PARTITION_CUSTOMER_PRIV_PARAM                SYSTEM_PARTITION_CUSTOMER_BEGIN

void ICACHE_FLASH_ATTR system_init_done();
void ICACHE_FLASH_ATTR udp_init(struct espconn* p_ptrespconn,int local_port);
void ICACHE_FLASH_ATTR scan_done(void *arg, STATUS status);
void ICACHE_FLASH_ATTR Wifi_conned(void *arg);
void ICACHE_FLASH_ATTR AP_UDP_Init();


#endif