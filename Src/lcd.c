/* Includes ------------------------------------------------------------------*/
#include "lcd.h"
//#include "hw_SSD1298.h"
#include "stm32f4xx_hal_gpio.h"
//#include "intrinsics.h"


#define _NOP     __no_operation()

GPIO_TypeDef* GPIO_PORT[LCD_ctrl_n] = {RST_GPIO_PORT,
                                       WR_GPIO_PORT,
                                       RD_GPIO_PORT,
                                       CS_GPIO_PORT,
                                       EN_GPIO_PORT,
                                       LE_GPIO_PORT,
                                       RS_GPIO_PORT};

const uint16_t GPIO_PIN[LCD_ctrl_n] = {RST_PIN,
                                       WR_PIN,
                                       RD_PIN,
                                       CS_PIN,
                                       EN_PIN,
                                       LE_PIN,
                                       RS_PIN};


//
//! LCD structure
//
LCD_Info tLcd;



void LCD_Initializtion(void)
{


}

void nopLoop(uint8_t count)
{
 // for(volatile uint8_t i = 0; i < count; ++i);
}


// Clear LCD control line
void SetP(Lcd_control signal)
{
    GPIO_PORT[signal]->BSRR = GPIO_PIN[signal];
}

// Set LCD control line
void ClrP(Lcd_control signal)
{
    GPIO_PORT[signal]->BSRR = GPIO_PIN[signal] << 16;
}

void BusWrite(uint16_t PortVal)
{
//    ClrP(LE);
//    DB_GPIO_PORT->ODR = PortVal;
//    SetP(LE);
//    _NOP; _NOP;
//    ClrP(LE);
//    DB_GPIO_PORT->ODR = PortVal>>8;
//    _NOP; _NOP;
}

void WrCmd(uint8_t cmd)
{
//    SetP(RD); _NOP; _NOP;
//    ClrP(RS); _NOP; _NOP;
//    ClrP(WR); _NOP; _NOP;
//    ClrP(CS); _NOP; _NOP;
//    BusWrite(cmd);
//    SetP(CS); _NOP; _NOP;
//    SetP(WR); _NOP; _NOP;
//    SetP(RS); _NOP; _NOP;
}

void WrData(uint16_t data)
{
//    SetP(RD); _NOP; _NOP;
//    SetP(RS); _NOP; _NOP;
//    ClrP(WR); _NOP; _NOP;
//    ClrP(CS); _NOP; _NOP;
//    BusWrite(data);
//    SetP(CS); _NOP; _NOP;
//    SetP(WR); _NOP; _NOP;
//    SetP(RS); _NOP; _NOP;
}

void WrAddr(unsigned int x, unsigned char y)
{
//	unsigned char xh, xl;
//		xh=x>>8;
//		xl=x;
//		WrCmd(xh);
//		WrCmd(xl);
//		WrCmd(y);
}

void InitScreen(uint16_t color)
{
//     unsigned long i;
//
//    i = tLcd.usHeight * tLcd.usWidth;
//    SetReg(R44h, 0 | (239 << 8));
//    SetReg(R45h, 0);
//    SetReg(R46h, 319);
//    SetReg(R4Eh, 0);
//    SetReg(R4Fh, 0);
//
//    //
//    //! Start writing GRAM
//    //
//    WrCmd(R22h);
//    while(i--)
//    {
//        WrData(color);
//    }
//
////////  uint16_t i, j;
////////  WrAddr(0,0);
////////  for(i=0;i<240;i++)
////////  {
////////      for (j=0;j<320;j++)
////////      WrData(color);
////////  }
}

uint8_t BusRead()
{
//    return DB_GPIO_PORT->ODR;
}

void SetReg(uint16_t index, uint16_t value)
{
//  WrCmd(index);
//  WrData(value);
}
