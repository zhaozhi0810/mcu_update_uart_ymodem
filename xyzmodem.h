/*
*********************************************************************************************************
*
*	模块名称 : XYZmodem协议
*	文件名称 : xyzmodem.h
*	版    本 : V1.0
*	说    明 : xyzmodem协议
*
*	修改记录 
*		版本号    日期         作者      说明
*		V1.0    2023-04-06     dazhi    首发
*
*	Copyright (C), 2022-2030, htjc by dazhi
*
*********************************************************************************************************
*/
#ifndef __XYZMODEM_H__
#define __XYZMODEM_H__

/*
*********************************************************************************************************
*	函 数 名: Ymodem_PrepareIntialPacket
*	功能说明: 准备第一包要发送的数据     
*	形    参: data 数据
*             fileName 文件名
*             length   文件大小
*	返 回 值: 0
*********************************************************************************************************
*/
void Ymodem_PrepareIntialPacket(uint8_t *data, const uint8_t* fileName, uint32_t *length);


/*
*********************************************************************************************************
*	函 数 名: Ymodem_PreparePacket
*	功能说明: 准备发送数据包    
*	形    参: SourceBuf 要发送的原数据
*             data      最终要发送的数据包，已经包含的头文件和原数据
*             pktNo     数据包序号
*             sizeBlk   要发送数据数
*	返 回 值: 无
*********************************************************************************************************
*/
void Ymodem_PreparePacket(uint8_t *SourceBuf, uint8_t *data, uint8_t pktNo, uint32_t sizeBlk);


/*
*********************************************************************************************************
*	函 数 名: UpdateCRC16
*	功能说明: 上次计算的CRC结果 crcIn 再加上一个字节数据计算CRC
*	形    参: crcIn 上一次CRC计算结果
*             byte  新添加字节
*	返 回 值: 无
*********************************************************************************************************
*/
uint16_t UpdateCRC16(uint16_t crcIn, uint8_t byte);


/*
*********************************************************************************************************
*	函 数 名: Cal_CRC16
*	功能说明: 计算一串数据的CRC
*	形    参: data  数据
*             size  数据长度
*	返 回 值: CRC计算结果
*********************************************************************************************************
*/
uint16_t Cal_CRC16(const uint8_t* data, uint32_t size);


/*
*********************************************************************************************************
*	函 数 名: CalChecksum
*	功能说明: 计算一串数据总和
*	形    参: data  数据
*             size  数据长度
*	返 回 值: 计算结果的后8位
*********************************************************************************************************
*/
uint8_t CalChecksum(const uint8_t* data, uint32_t size);


/*
*********************************************************************************************************
*	函 数 名: Ymodem_Transmit
*	功能说明: 发送文件
*	形    参: buf  文件数据
*             sendFileName  文件名
*             sizeFile    文件大小
*	返 回 值: 0  文件发送成功
*********************************************************************************************************
*/
uint8_t Ymodem_Transmit (uint8_t *buf, const uint8_t* sendFileName, uint32_t sizeFile);


/*
*********************************************************************************************************
*	函 数 名: xymodem_send
*	功能说明: 发送文件
*	形    参: filename  文件名
*	返 回 值: 0  文件发送成功
*********************************************************************************************************
*/
int xymodem_send(const char *filename);


#endif
