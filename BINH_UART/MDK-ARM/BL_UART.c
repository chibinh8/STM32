#include "BL_UART.h"

uint16_t len;
char Transfer_cplt, Rx_indx;
//Interrupt callback routine
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t i;
	if (huart->Instance == USART2)	//current UART
		{
		if (Rx_indx==0) {for (i=0;i<SIZEOFBUFFER;i++) Rx_Buffer[i]=0;}	//clear Rx_Buffer before receiving new data	
		
		if (Rx_data[0]!=13)	//if received data different from ascii 13 (enter)
			{
			Rx_Buffer[Rx_indx++]=Rx_data[0];	//add data to Rx_Buffer
			}
		else			//if received data = 13
			{
			Rx_indx=0;
			Transfer_cplt=1;//transfer complete, data is ready to read
			}

		HAL_UART_Receive_IT(huart, (uint8_t*)Rx_data, 1);	//activate UART receive interrupt every time
		}
}

//Binh Le: Finally adapt for using
BL_GetDataSta BL_GetReceivedData_UART(UART_HandleTypeDef *huart){

	  if(Transfer_cplt==1){
		HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12);
		Transfer_cplt=0;	
		return E_OK;
	 }
	 else 
		return E_NOTOK;
}

void BL_SendData2PC_UART(UART_HandleTypeDef *huart,char *t_SentDta)
{		char buffer[SIZEOFBUFFER];			
		//print out variable
	  sprintf(buffer,"%s", t_SentDta);
		len=strlen(buffer);
		HAL_UART_Transmit(huart, (uint8_t*)buffer, len, 1000);
		HAL_UART_Receive_IT(huart, (uint8_t*)Rx_data, 1);	
		HAL_Delay(100);
}



