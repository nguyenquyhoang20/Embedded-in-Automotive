/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stdint.h>

//#include "default.h"
#include "rcc.h"
#include "t_delay.h"
#include "gpio.h"

#include "uart.h"



/*
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
*/

#include "stm32f1xx.h"


char rx_buf[1025];
char tx_buf[10];

int main(void)
{

	 system_clk();
	 uart_init();
	 timer_initialise();
	 uart_tran_string("Uart stm32 device driver\n");
	 uart_tran_string("Kunal Gupta\n");


	while(1)
	{
		 uart_tran_byte('k');
		 uart_tran_string("Subscribe to Gettobyte\n");
		 uart_tran_string("Send data from console\n");
		 uart_rec(rx_buf);
		 uart_tran_string(rx_buf);

		delay_ms(100);
	}
}

