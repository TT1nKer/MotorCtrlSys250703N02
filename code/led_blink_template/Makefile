# Makefile for STM32F4 bare-metal project

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
CFLAGS=-mcpu=cortex-m4 -mthumb -O2 -Wall -nostdlib -nostartfiles
LDFLAGS=-Tstm32f4.ld

all: led_blink.bin

led_blink.elf: main.c startup_stm32f4xx.s stm32f4.ld
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ main.c startup_stm32f4xx.s

led_blink.bin: led_blink.elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f *.elf *.bin