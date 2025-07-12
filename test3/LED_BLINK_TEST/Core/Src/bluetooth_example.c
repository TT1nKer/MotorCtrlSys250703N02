/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    bluetooth_example.c
  * @brief   Example code for Bluetooth module communication
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "spi.h"
#include <string.h>

/* Private defines -----------------------------------------------------------*/
#define BT_BUFFER_SIZE 256
#define SPI_BUFFER_SIZE 32

/* Private variables ---------------------------------------------------------*/
uint8_t bt_rx_buffer[BT_BUFFER_SIZE];
uint8_t spi_tx_buffer[SPI_BUFFER_SIZE];
uint8_t spi_rx_buffer[SPI_BUFFER_SIZE];

/* Private function prototypes -----------------------------------------------*/
void BT_SendCommand(const char* command);
void BT_ReceiveResponse(uint8_t* buffer, uint16_t size);
void SPI_SendData(uint8_t* data, uint16_t size);
void SPI_ReceiveData(uint8_t* data, uint16_t size);

/* USER CODE BEGIN 0 */

/**
  * @brief  Send AT command to Bluetooth module
  * @param  command: AT command string
  * @retval None
  */
void BT_SendCommand(const char* command)
{
  HAL_UART_Transmit(&huart2, (uint8_t*)command, strlen(command), 1000);
  HAL_Delay(100); // Wait for module to process
}

/**
  * @brief  Receive response from Bluetooth module
  * @param  buffer: Buffer to store received data
  * @param  size: Size of buffer
  * @retval Number of bytes received
  */
void BT_ReceiveResponse(uint8_t* buffer, uint16_t size)
{
  HAL_UART_Receive(&huart2, buffer, size, 1000);
}

/**
  * @brief  Send data via SPI
  * @param  data: Data to send
  * @param  size: Size of data
  * @retval None
  */
void SPI_SendData(uint8_t* data, uint16_t size)
{
  // CS low
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
  
  // Send data
  HAL_SPI_Transmit(&hspi1, data, size, 1000);
  
  // CS high
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

/**
  * @brief  Receive data via SPI
  * @param  data: Buffer to store received data
  * @param  size: Size of data to receive
  * @retval None
  */
void SPI_ReceiveData(uint8_t* data, uint16_t size)
{
  // CS low
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
  
  // Receive data
  HAL_SPI_Receive(&hspi2, data, size, 1000);
  
  // CS high
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
}

/**
  * @brief  Example: Initialize HC-05 Bluetooth module
  * @retval None
  */
void BT_HC05_Init(void)
{
  // Send AT commands to configure HC-05
  BT_SendCommand("AT\r\n");
  HAL_Delay(1000);
  
  BT_SendCommand("AT+NAME=STM32_BT\r\n");
  HAL_Delay(1000);
  
  BT_SendCommand("AT+PSWD=1234\r\n");
  HAL_Delay(1000);
  
  BT_SendCommand("AT+UART=9600,0,0\r\n");
  HAL_Delay(1000);
}

/**
  * @brief  Example: Send data to Bluetooth device
  * @param  message: Message to send
  * @retval None
  */
void BT_SendMessage(const char* message)
{
  HAL_UART_Transmit(&huart2, (uint8_t*)message, strlen(message), 1000);
}

/**
  * @brief  Example: Receive data from Bluetooth device
  * @param  buffer: Buffer to store received data
  * @param  max_size: Maximum size of buffer
  * @retval Number of bytes received
  */
uint16_t BT_ReceiveMessage(uint8_t* buffer, uint16_t max_size)
{
  return HAL_UART_Receive(&huart2, buffer, max_size, 100);
}

/**
  * @brief  Example: SPI communication with nRF24L01 module
  * @retval None
  */
void SPI_nRF24L01_Example(void)
{
  uint8_t config_data[] = {0x20, 0x0F}; // CONFIG register
  uint8_t status;
  
  // Write configuration
  SPI_SendData(config_data, 2);
  
  // Read status
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi1, (uint8_t[]){0xFF}, 1, 1000); // Dummy byte
  HAL_SPI_Receive(&hspi1, &status, 1, 1000);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

/* USER CODE END 0 */ 