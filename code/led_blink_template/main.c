// NOTE: This template assumes you are using STM32CubeIDE or a similar toolchain with STM32F4 HAL/StdPeriph drivers.
// Make sure 'stm32f4xx.h' is available in your include path.
// Define LED pin (e.g., PD12 on STM32F407VET6 Discovery board)
#define LED_PORT GPIOD
#define LED_PIN  GPIO_PIN_12

#define PERIPH_BASE           ((unsigned int)0x40000000)
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000)
#define GPIOD_BASE            (AHB1PERIPH_BASE + 0x0C00)
#define RCC_BASE              (AHB1PERIPH_BASE + 0x3800)

#define RCC_AHB1ENR           (*(volatile unsigned int *)(RCC_BASE + 0x30))
#define GPIOD_MODER           (*(volatile unsigned int *)(GPIOD_BASE + 0x00))
#define GPIOD_OTYPER          (*(volatile unsigned int *)(GPIOD_BASE + 0x04))
#define GPIOD_PUPDR           (*(volatile unsigned int *)(GPIOD_BASE + 0x0C))
#define GPIOD_ODR             (*(volatile unsigned int *)(GPIOD_BASE + 0x14))

#define GPIODEN               (1 << 3)
#define LED_PIN               12

void LED_Init(void) {
    RCC_AHB1ENR |= GPIODEN; // Enable GPIOD clock
    GPIOD_MODER &= ~(0x3 << (LED_PIN * 2));
    GPIOD_MODER |=  (0x1 << (LED_PIN * 2)); // Output mode
    GPIOD_OTYPER &= ~(0x1 << LED_PIN);      // Push-pull
    GPIOD_PUPDR &= ~(0x3 << (LED_PIN * 2)); // No pull-up/pull-down
}

void delay(volatile unsigned int t) {
    while (t--) for (volatile unsigned int i = 0; i < 8000; i++);
}

int main(void) {
    LED_Init();
    while (1) {
        GPIOD_ODR ^= (1 << LED_PIN); // Toggle LED
        delay(100);
    }
} 