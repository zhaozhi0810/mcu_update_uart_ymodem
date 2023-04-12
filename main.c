/*
*********************************************************************************************************
*
*	ģ������ : ������
*	�ļ����� : main.c
*	��    �� : V1.0
*	˵    �� : ������
*
*	�޸ļ�¼ 
*		�汾��    ����         ����      ˵��
*		V1.0    2023-04-06     dazhi    �׷�
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
 /* Դ�ļ�·�� */
//char SourceFile[] = "./app.bin";    
static const char* my_opt = "f:";

void send_update_cmd_tomcu(void)
{
	uint8_t buf[] = {0xa5,74,0,0xef};   //��������
	UART_SendPacket(buf, 4);   //4���ֽڷ���ȥ
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
	        if(get_name)  //������ѭ��
	        	break;
	    }
	}
	uart_init(argc, argv);

	system("/root/drv722api_disable_wtd");
	system("killall drv722_22134_server");   //ɱ������

	
	do{
		ret = UART_ReceiveByte (data, 1);  //���������1���ַ�(��һ��)����һ�����ԣ�ֻ�ȴ�2ms
	}while(ret==0);
	
	if(data[0] != 0x43)
		send_update_cmd_tomcu();

	//sleep(1);

    if(0 == xymodem_send(filename))
    	printf("%s is over!\n",argv[0]);

    uart_exit() ;

    return 0;
}


