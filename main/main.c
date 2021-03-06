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
	uint8_t rng[32];
	uint8_t serialnum[9];
	int i;
	bool config_locked;
	bool data_locked;
	
	/*
		Change this configuration as needed
		I2C pins are defined in components/cryptoauthlib/src/hal_esp8266_i2c.c
	*/
	ATCAIfaceCfg cfg = 
	{
		.devtype = ATECC608A,
		.atcai2c.bus = I2C_NUM_0,
		.atcai2c.baud = 400000,
		.wake_delay = 1500,
		.rx_retries = 20,
	};

	// Initialize the crypto chip
	printf("Initializing chip\n");
	int ret = -1;
	for(int i = 0; i < 128; i++)
	{
		cfg.atcai2c.slave_address = i;
		ret = atcab_init(&cfg);
		if(ret == ATCA_SUCCESS) break;
	}
	assert(ret == ATCA_SUCCESS);

	// Get the crypto chip serial number
	assert(ATCA_SUCCESS == atcab_read_serial_number(serialnum));

	// Get a random 32-byte number from the crypto chip
	assert(ATCA_SUCCESS == atcab_random(rng));

	// Check lock status of zones
	assert(ATCA_SUCCESS == atcab_is_locked(LOCK_ZONE_CONFIG, &config_locked));
	assert(ATCA_SUCCESS == atcab_is_locked(LOCK_ZONE_DATA, &data_locked));

	/*
		Print results
	*/

	printf("Your serial ID:\n");
	for(i = 0; i < 9; i++) printf("%02X ", serialnum[i]);

	printf("\n\nYour random number:\n");
	for(i = 0; i < 32; i++)
	{
		printf("%02X ", rng[i]);
		if((i + 1) % 8 == 0) printf("\n");
	}

	printf("\n");
	if(config_locked) printf("Config zone is locked\n");
	else printf("Config zone is unlocked\n");

	if(data_locked) printf("Data zone is locked\n");
	else printf("Data zone is unlocked\n");
}
