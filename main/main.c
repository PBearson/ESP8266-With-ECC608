/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "cryptoauthlib.h"
#include "driver/i2c.h"
#include "esp_system.h"

void app_main()
{
	// Change this configuration as needed
	// I2C pins are defined in hal_esp8266_i2c.c
	ATCAIfaceCfg cfg = 
	{
		.devtype = ATECC608A,
		.atcai2c.bus = I2C_NUM_0,
		.atcai2c.slave_address = 0x20,
		.atcai2c.baud = 400000,
		.wake_delay = 1500,
		.rx_retries = 20,
	};

	uint8_t rng[32];
	uint8_t serialnum[9];
	int i;

	// Initialize the crypto chip
	assert(ATCA_SUCCESS == atcab_init(&cfg));

	// Get the crypto chip serial number
	assert(ATCA_SUCCESS == atcab_read_serial_number(serialnum));

	// Get a random 32-byte number from the crypto chip
	assert(ATCA_SUCCESS == atcab_random(rng));

	printf("Your serial ID:\n");
	for(i = 0; i < 9; i++) printf("%02X ", serialnum[i]);

	printf("\n\nYour random number:\n");
	for(i = 0; i < 32; i++)
	{
		printf("%02X ", rng[i]);
		if((i + 1) % 8 == 0) printf("\n");
	}
}
