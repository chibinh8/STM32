#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
#undef HAL_RCC_MODULE_ENABLED
#ifndef HALINCLUDE
#include "stm32f4xx_hal.h"
#endif
#include "stm32f4xx_hal_uart.h"
#include <string.h>
#define SIZEOFBUFFER 100
#if defined UART2
 UART_HandleTypeDef huart2;
#endif
typedef enum GetDataSta{	
	E_OK = 0,
	E_NOTOK,
}BL_GetDataSta;

extern char Rx_data[2];
//string of data recevied
extern char Rx_Buffer[SIZEOFBUFFER];
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
BL_GetDataSta BL_GetReceivedData_UART(UART_HandleTypeDef *huart);
void BL_SendData2PC_UART(UART_HandleTypeDef *huart,char *t_SentDta);



