/*
*********************************************************************************************************
*
*	Ä£¿éÃû³Æ : Ö÷º¯Êý
*	ÎÄ¼þÃû³Æ : main.c
*	°æ    ±¾ : V1.0
*	Ëµ    Ã÷ : Ö÷¹¦ÄÜ
*
*	ÐÞ¸Ä¼ÇÂ¼ 
*		°æ±¾ºÅ    ÈÕÆÚ         ×÷Õß      ËµÃ÷
*		V1.0    2023-04-06     dazhi    Ê×·¢
*
*	Copyright (C), 2022-2030, htjc by dazhi
*
*
*    aarch64-linux-gnu-gcc *.c -o xyzmodem_send
*********************************************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"
#include "uart_to_mcu.h"
#include "xyzmodem.h"
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
 /* Ô´ÎÄ¼þÂ·¾¶ */
//char SourceFile[] = "./app.bin";    
static const char* my_opt = "f:";
char md5_readBuf[64] = {0};


void send_update_cmd_tomcu(void)
{
	uint8_t buf[] = {0xa5,74,0,0xef};   //Éý¼¶ÃüÁî
	UART_SendPacket(buf, 4);   //4¸ö×Ö½Ú·¢³öÈ¥
}


int get_file_md5sum(char * filename)
{
	FILE * filep;
	char cmd[128] = {"md5sum "};
	
	int ret;

	strcat(cmd,filename);

	filep = popen(cmd,"r");
	if(!filep)
		return -1;
    ret = fread(md5_readBuf,32,1,filep);
 
    printf("get_file_md5sum = %s ,ret= %d\n",md5_readBuf,ret);

    pclose(filep);

    return ret;
}




int main(int argc,char* argv[]) 
{
	char* filename = "./app.bin";
	int get_name = 0;
	int c,ret;
	char data[2] = {0};
	int offset=0;


    if(argc != 1)
	{	
	    while(1)
	    {
	        c = getopt(argc, argv, my_opt);
	        //printf("optind: %d\n", optind);
	        if (c < 0)
	        {
	            break;
	        }
	        //printf("option char: %x %c\n", c, c);
	        switch(c)
	        {
	        	case 'f':
	        		filename = optarg;
	        		get_name = 1;
	                //debug_level = atoi(optarg);
	                printf("filename = %s\n",filename);
	                break;	       
	       	 	default:	       
	                break;
	                //return 0;
	        }
	        if(get_name)  //Ìø³ö´óÑ­»·
	        	break;
	    }
	}

	ret = get_file_md5sum(filename);
	if(ret)
	{
		printf("buf = %s,strlen = %lu\n",md5_readBuf,strlen(md5_readBuf));
	}

	uart_init(argc, argv);

	system("/root/drv722api_disable_wtd");
	system("killall drv722_22134_server");   //杀掉进程

	
	do{
		ret = UART_ReceiveByte (data, 1);  //读取缓存的字符
	}while(ret==0);
	
	if(data[0] != 0x43)
		send_update_cmd_tomcu();

	//sleep(1);

    if(0 == xymodem_send(filename))
    	printf("%s is done!\n",argv[0]);

    uart_exit() ;

    return 0;
}


