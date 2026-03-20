#ifndef __DHT11_H__
#define __DHT11_H__

#include "main.h"

void DHT11_Start(void);
uint8_t DHT11_Check_Response(void);
uint8_t DHT11_Read(void);
void DHT11_Read_Data(uint8_t *temp, uint8_t *hum);

#endif
