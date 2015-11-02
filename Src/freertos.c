/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  *
  * COPYRIGHT(c) 2015 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "usbd_cdc_if.h"
#include "lcd.h"
#include "spi.h"
#include "stm32f4_discovery.h"

/* USER CODE BEGIN Includes */     
/* Buffer used for transmission */
uint8_t aTxBufferY[] = {0x90, 0, 0};
uint8_t aTxBufferX[] = {0xD0, 0, 0};

uint8_t aRxBufferY[] = {0, 0, 0};
uint8_t aRxBufferX[] = {0, 0, 0};

uint16_t X_pos_ = 0;
uint16_t Y_pos_ = 0;

uint16_t x1 = 0;
uint16_t x2 = 0;

//uint16_t y1 = 0;
//uint16_t y2 = 0;

/* Buffer used for reception */
//uint8_t aRxBuffer[BUFFERSIZE];
/* USER CODE END 0 */

#define	CMD_RDX 	0x94 // 12 bit conv, sigle-ended, Y-measure
#define	CMD_RDY 	0xD4 // 12 bit conv, sigle-ended, X-measure
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;

/* USER CODE BEGIN Variables */
extern SPI_HandleTypeDef hspi3;
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  uint8_t Xarray[] = "X = ";
  uint8_t Yarray[] = " Y = ";
  uint8_t NewLine[] = "\r\n";
  uint16_t sizeOf_Xarray = sizeof(Xarray)/sizeof(Xarray[0]) - 1;
  uint16_t sizeOf_Yarray = sizeof(Yarray)/sizeof(Yarray[0]) - 1;
  uint16_t sizeOf_NewLine = sizeof(NewLine)/sizeof(NewLine[0]) - 1;

  uint8_t Xstring[] = "       ";
  uint8_t Ystring[] = "       ";
  uint16_t sizeOf_string = sizeof(Ystring)/sizeof(Ystring[0]) - 1;
  HAL_Delay(1000);

  ClrP( SPI3_CS );

  float X_resolution = (float)3780 / 640;
  float Y_resolution = (float)3600 / 480;

  uint32_t X_640_old = 0;
  uint32_t Y_480_old = 0;

  for(;;)
  {
	BSP_LED_Toggle(LED4);
    osDelay(10);

    HAL_SPI_TransmitReceive(&hspi3,(uint8_t*)aTxBufferY, (uint8_t *)aRxBufferY, 3, 500);
    HAL_SPI_TransmitReceive(&hspi3,(uint8_t*)aTxBufferX, (uint8_t *)aRxBufferX, 3, 500);
    uint32_t *Y_temp = (uint32_t*)(aRxBufferX);
    uint32_t *X_temp = (uint32_t*)(aRxBufferY);

    uint32_t Y_temp1 = *Y_temp;
    uint32_t X_temp1 = *X_temp;

    X_temp1 >>= 8;
    uint32_t X_temp1_rev_first7_bits = 0x7F & X_temp1;
    X_temp1 >>= 11;
    X_temp1 = X_temp1 | (X_temp1_rev_first7_bits<<5);

    Y_temp1 >>= 8;
    uint32_t Y_temp1_rev_first7_bits = 0x7F & Y_temp1;
    Y_temp1 >>= 11;
    Y_temp1 = Y_temp1 | (Y_temp1_rev_first7_bits<<5);


    if( Y_temp1 != 0x000 )
    {
        if( 3900 < X_temp1) { X_temp1 = 3900; }
        if( (120 > X_temp1) && (0 != X_temp1) ) { X_temp1 = 120; }

        if( 3800 < Y_temp1) { Y_temp1 = 3800; }
        if( (200 > Y_temp1) && (0 != Y_temp1) ) { Y_temp1 = 200; }

        X_temp1 = X_temp1 - 3900;
        X_temp1 = abs(X_temp1);

        uint32_t X_640 = X_temp1/X_resolution;
        uint32_t Y_480 = (Y_temp1 - 200)/Y_resolution;

    	if( (X_640 != X_640_old) || (Y_480 != Y_480_old) )
    	{
    		itoa(X_640, (char*)Xstring, 10);
    		itoa(Y_480, (char*)Ystring, 10);

            CDC_Transmit_FS( Xarray,  sizeOf_Xarray );
            HAL_Delay(1);
            CDC_Transmit_FS( Xstring,  sizeOf_string );
            HAL_Delay(1);
            CDC_Transmit_FS( Yarray,  sizeOf_Yarray );
            HAL_Delay(1);
            CDC_Transmit_FS( Ystring,  sizeOf_string );
            HAL_Delay(1);
            CDC_Transmit_FS( NewLine, sizeOf_NewLine );
            HAL_Delay(10);
            BSP_LED_Toggle(LED5);
            X_640_old = X_640;
            Y_480_old = Y_480;
    	}
    }

    // clearing
    uint16_t i = 0;
    for(i = 0; i < 3; ++i )
    {
    	aRxBufferY[i] = 0;
    	aRxBufferX[i] = 0;
    }

    for( i=0; i<sizeOf_string; ++i)
    {
    	Xstring[i] = ' ';
    	Ystring[i] = ' ';
    }


  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
