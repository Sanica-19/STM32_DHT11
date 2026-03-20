#include "dht11.h"

extern TIM_HandleTypeDef htim2;

#define DHT11_PORT GPIOA
#define DHT11_PIN  GPIO_PIN_1

void delay_us(uint16_t us)
{
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    while (__HAL_TIM_GET_COUNTER(&htim2) < us);
}

void DHT11_Start(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Set pin as output
    GPIO_InitStruct.Pin = DHT11_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);

    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET);
    HAL_Delay(18);

    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET);
    delay_us(20);

    // Set pin as input
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);
}

uint8_t DHT11_Check_Response(void)
{
    uint8_t response = 0;
    delay_us(40);

    if (!HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))
    {
        delay_us(80);
        if (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)) response = 1;
    }

    while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN));
    return response;
}

uint8_t DHT11_Read(void)
{
    uint8_t i = 0, j;

    for (j = 0; j < 8; j++)
    {
        while (!HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN));
        delay_us(40);

        if (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))
            i |= (1 << (7 - j));

        while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN));
    }
    return i;
}

void DHT11_Read_Data(uint8_t *temp, uint8_t *hum)
{
    uint8_t Rh1, Rh2, Temp1, Temp2, checksum;

    DHT11_Start();
    DHT11_Check_Response();

    Rh1 = DHT11_Read();
    Rh2 = DHT11_Read();
    Temp1 = DHT11_Read();
    Temp2 = DHT11_Read();
    checksum = DHT11_Read();

    *temp = Temp1;
    *hum  = Rh1;
}
