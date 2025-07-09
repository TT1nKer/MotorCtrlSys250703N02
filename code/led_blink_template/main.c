// NOTE: This template assumes you are using STM32CubeIDE or a similar toolchain with STM32F4 HAL/StdPeriph drivers.
// Make sure 'stm32f4xx.h' is available in your include path.
#include "stm32f4xx.h"

// Define LED pin (e.g., PD12 on STM32F407VET6 Discovery board)
#define LED_PORT GPIOD
#define LED_PIN  GPIO_PIN_12

void LED_Init(void) {
    // Enable GPIOD clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    // Set PD12 as output
    LED_PORT->MODER &= ~(0x3 << (LED_PIN * 2));
    LED_PORT->MODER |=  (0x1 << (LED_PIN * 2));
    // Output push-pull
    LED_PORT->OTYPER &= ~(0x1 << LED_PIN);
    // No pull-up, pull-down
    LED_PORT->PUPDR &= ~(0x3 << (LED_PIN * 2));
}

void delay(volatile uint32_t t) {
    while (t--) {
        for (volatile uint32_t i = 0; i < 8000; i++);
    }
}

int main(void) {
    LED_Init();
    while (1) {
        // Toggle LED
        LED_PORT->ODR ^= (1 << LED_PIN);
        delay(100);
    }
} 