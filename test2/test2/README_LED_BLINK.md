# LED Blink Program for PD12

This project demonstrates a simple LED blinking program using PD12 pin on an STM32F4 microcontroller.

## Hardware Requirements

- STM32F4 development board
- LED connected to PA12 (with appropriate current-limiting resistor)
- Power supply for the development board

## Circuit Connection

```
PD12 ----[220Ω Resistor]---- LED ---- GND
```

## Program Description

The program performs the following operations:

1. **Initialization**: 
   - Initializes the HAL (Hardware Abstraction Layer)
   - Configures the system clock
   - Initializes PA12 as a GPIO output pin

2. **Main Loop**:
   - Toggles the LED state (ON/OFF) every 500ms
   - Uses `HAL_GPIO_TogglePin()` function to toggle PD12
   - Uses `HAL_Delay()` for timing

## Key Functions Used

- `HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12)`: Toggles the PD12 pin state
- `HAL_Delay(500)`: Creates a 500ms delay
- `MX_GPIO_Init()`: Initializes GPIO configuration

## GPIO Configuration

PD12 is configured as:
- **Mode**: Output Push-Pull
- **Speed**: Low frequency
- **Pull-up/Pull-down**: No pull
- **Initial State**: Low (LED OFF)

## Building and Flashing

1. Open the project in STM32CubeIDE
2. Build the project (Project → Build All)
3. Connect your STM32F4 board
4. Flash the program (Run → Debug)

## Expected Behavior

The LED connected to PD12 should blink with a 1-second period (500ms ON, 500ms OFF).

## Modifying the Blink Rate

To change the blink rate, modify the delay value in the main loop:

```c
HAL_Delay(1000);  // 1 second delay
HAL_Delay(250);   // 250ms delay
```

## Troubleshooting

1. **LED doesn't blink**: Check the circuit connection and ensure the LED is properly connected to PD12
2. **Wrong blink rate**: Verify the delay value in the code
3. **Compilation errors**: Ensure all HAL libraries are properly included 