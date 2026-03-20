#include "lcd_i2c.h"

extern I2C_HandleTypeDef hi2c1;

#define LCD_ADDR (0x27 << 1)

void lcd_send_cmd(char cmd)
{
    uint8_t data_u = cmd & 0xF0;
    uint8_t data_l = (cmd << 4) & 0xF0;
    uint8_t data[4];

    data[0] = data_u | 0x0C;
    data[1] = data_u | 0x08;
    data[2] = data_l | 0x0C;
    data[3] = data_l | 0x08;

    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, data, 4, 100);
}

void lcd_send_data(char data)
{
    uint8_t data_u = data & 0xF0;
    uint8_t data_l = (data << 4) & 0xF0;
    uint8_t data_buf[4];

    data_buf[0] = data_u | 0x0D;
    data_buf[1] = data_u | 0x09;
    data_buf[2] = data_l | 0x0D;
    data_buf[3] = data_l | 0x09;

    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, data_buf, 4, 100);
}

void lcd_init(void)
{
    HAL_Delay(50);

    lcd_send_cmd(0x30);
    HAL_Delay(5);
    lcd_send_cmd(0x30);
    HAL_Delay(1);
    lcd_send_cmd(0x30);

    lcd_send_cmd(0x20);
    lcd_send_cmd(0x28);
    lcd_send_cmd(0x08);
    lcd_send_cmd(0x01);
    HAL_Delay(2);
    lcd_send_cmd(0x06);
    lcd_send_cmd(0x0C);
}

void lcd_send_string(char *str)
{
    while (*str) lcd_send_data(*str++);
}

void lcd_clear(void)
{
    lcd_send_cmd(0x01);
    HAL_Delay(2);
}

void lcd_set_cursor(int row, int col)
{
    uint8_t pos = (row == 0 ? 0x80 : 0xC0) + col;
    lcd_send_cmd(pos);
}
