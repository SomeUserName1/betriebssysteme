// Fabian Klopfer
// Jannik Bamberger
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define GPIO1_START 0x4804C000
#define GPIO1_END 0x4804E000
#define GPIO1_SIZE (GPIO1_END - GPIO1_START)
#define GPIO_SET_CLEAR 0x190 //Clear-register offset
#define GPIO_SET_OUT 0x194   //Set-register offset

#define LED0 (1<<21)
#define LED1 (1<<22)
#define LED2 (1<<23)
#define LED3 (1<<24)
#define ALL_LEDS (LED0 | LED1 | LED2 | LED3)

#define SLEEP_TIME 100000 // time in useconds between states

volatile void *gpio_addr;
volatile unsigned int *gpio_set;
volatile unsigned int *gpio_reset;

/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 18
 * @bonus10
 */

int main(void)
{
	/* clean the led config files */
	system("echo none > /sys/class/leds/beaglebone\\:green\\:usr0/trigger");
	system("echo none > /sys/class/leds/beaglebone\\:green\\:usr1/trigger");
	system("echo none > /sys/class/leds/beaglebone\\:green\\:usr2/trigger");
	system("echo none > /sys/class/leds/beaglebone\\:green\\:usr3/trigger");


	int leds[] = {LED0, LED1, LED2, LED3};
	int file = open("/dev/mem", O_RDWR);
	// error condition? (-3)

	gpio_addr = mmap(NULL, GPIO1_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
					 file, GPIO1_START);
	// error condition? (-3)

	gpio_set = gpio_addr + GPIO_SET_OUT;
	gpio_reset = gpio_addr + GPIO_SET_CLEAR;
	// 2x warning: pointer of type ‘void *’ used in arithmetic (1x -3)

	int direction = 1;
	int cnt = 0;

	while (1) {
		if (cnt == 3)
			direction = -1;
		if (cnt == 0)
			direction = 1;
		if (direction > 0)
			cnt++;
		else
			cnt--;

		*gpio_reset = ALL_LEDS;
		*gpio_set = leds[cnt];
		// warning: conversion to ‘unsigned int’ from ‘int’ may change the sign of the result (-3)

		usleep(SLEEP_TIME);
	}
	return 0;
}
