/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    bluetooth_example.h
  * @brief   Header file for Bluetooth module communication examples
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BLUETOOTH_EXAMPLE_H__
#define __BLUETOOTH_EXAMPLE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
void BT_SendCommand(const char* command);
void BT_ReceiveResponse(uint8_t* buffer, uint16_t size);
void SPI_SendData(uint8_t* data, uint16_t size);
void SPI_ReceiveData(uint8_t* data, uint16_t size);
void BT_HC05_Init(void);
void BT_SendMessage(const char* message);
uint16_t BT_ReceiveMessage(uint8_t* buffer, uint16_t max_size);
void SPI_nRF24L01_Example(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ BLUETOOTH_EXAMPLE_H__ */ 