#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"

#define LED_PIN 12

void LED_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // Enable GPIOD clock
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    
    // Configure PD12 as output
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    // Initialize LED to OFF state
    PDout(LED_PIN) = 0;
}

int main(void)
{
    // Initialize delay system
    delay_init(168);  // 168MHz system clock
    
    // Initialize LED GPIO
    LED_GPIO_Init();
    
    while(1)
    {
        // Turn LED ON
        PDout(LED_PIN) = 1;
        delay_ms(500);  // Wait 500ms
        
        // Turn LED OFF
        PDout(LED_PIN) = 0;
        delay_ms(500);  // Wait 500ms
    }
} 