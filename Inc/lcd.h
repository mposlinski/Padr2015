
#ifndef __lcd_H
#define __lcd_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
//#include "stm32f4xx_hal_gpio.h"

   
/* LCD color */
#define WHITE           0xFFFF
#define BLACK           0x0000
#define GREY            0xF7DE
#define BLUE            0x001F
#define BLUE2           0x051F
#define RED             0xF800
#define MAGNETA         0xF81F
#define GREEN           0x07E0
#define CYAN            0x7FFF
#define YELLOW          0xFFE0

#define SMALL 0
#define MEDIUM 1
#define LARGE 2


//#define RED 0xc0
//#define GREEN 0x1c
//#define BLUE 0x03
//#define CYAN 0x1F
//#define YELLOW 0xFC
//#define MAGENTA 0xE3
  
//   Cocox
//00042 #define COLOR_WHITE              0xFFFF
//00043 #define COLOR_BLACK              0x0000
//#define COLOR_BLUE               0x001F
//#define COLOR_BRED               0XF81F
//00046 #define COLOR_GRED               0XFFE0
//00047 #define COLOR_GBLUE              0X07FF
//00048 #define COLOR_RED                0xF800
//00049 #define COLOR_MAGENTA            0xF81F
//00050 #define COLOR_GREEN              0x07E0
//00051 #define COLOR_CYAN               0x7FFF
//00052 #define COLOR_YELLOW             0xFFE0
//00053 #define COLOR_BROWN              0XBC40
//00054 #define COLOR_BRRED              0XFC07
//00055 #define COLOR_GRAY               0X8430
//00056 
//00057 #define COLOR_DARKBLUE           0X01CF
//00058 #define COLOR_LIGHTBLUE          0X7D7C
//00059 #define COLOR_GRAYBLUE           0X5458
//00060 
//00061 #define COLOR_LIGHTGREEN         0X841F
//00062 #define COLOR_LIGHTGRAY          0XEF5B
//00063 #define COLOR_LGRAY              0XC618
//00064 #define COLOR_LGRAYBLUE          0XA651
//00065 #define COLOR_LBBLUE             0X2B12  
   
   
   
   
   
 typedef enum
 {
   SPI3_CS  = 0,
   WR   	= 1,
   RD   	= 2,
   CS   	= 3,
   EN   	= 4,
   LE   	= 5,
   RS   	= 6
 } Lcd_control;


//
//! Default LCD information structure
//
typedef struct
{
	unsigned short usWidth;
	unsigned short usHeight;
	unsigned short usID;
	unsigned char ucOrientation;
} LCD_Info;
 
 
 
#define LCD_ctrl_n              7   // number of control signals

#define RST_PIN                 GPIO_PIN_15
#define RST_GPIO_PORT           GPIOA

#define WR_PIN                  GPIO_PIN_3
#define WR_GPIO_PORT            GPIOB

#define RD_PIN                  GPIO_PIN_15
#define RD_GPIO_PORT            GPIOA

#define CS_PIN                  GPIO_PIN_4
#define CS_GPIO_PORT            GPIOB

#define EN_PIN                  GPIO_PIN_9
#define EN_GPIO_PORT            GPIOA

#define LE_PIN                  GPIO_PIN_8
#define LE_GPIO_PORT            GPIOA

#define RS_PIN                  GPIO_PIN_5      //RS - Register Select (Data/Command bit)
#define RS_GPIO_PORT            GPIOB


#define DB_GPIO_PORT            GPIOD   // Data bus port lower 8 bit


void LCD_Initializtion(void);
void SetP(Lcd_control signal);
void ClrP(Lcd_control signal);
void BusWrite(uint16_t PortVal);
void WrCmd(uint8_t cmd);
void WrData(uint16_t data);
void WrAddr(unsigned int x, unsigned char y);
void InitScreen(uint16_t color);
void SetReg(uint16_t index, uint16_t value);


#ifdef __cplusplus
}
#endif

#endif /* __lcd_H */
