/*
 * IoT-Labs-2018 
 * Copyright (C) 2018 Massinissa Hamidi 
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>

#include "nvs_flash.h"

#include "connectivity.h"
#include "sensor_reading.h"
#include "transmission.h"


int
app_main()
{
    int rc = 0;

    nvs_flash_init();

    rc = transmission_init();
    if (rc < 0) {
        printf("[IoT-Labs] Error while initializing transmission\n");
        return rc;
    }

    /* setup_connectivity will launch a task which will be responsible of
     * transmitting data from the esp32 to a given server specified by
     * HOSTNAME.
     */
    struct conn_config_t conn_cfg = {
        .phy_proto=WIFI,
        .net_proto=IPv4,
        .trans_proto=TCP,
        .app_proto=HTTP,
    };

    xTaskCreate(&setup_connectivity, "setup_connectivity", 4096, &conn_cfg, 1,
            NULL);
    

    /* setup_sensors will, eventually, launch a task which, in a continuous
     * manner, will get measures from connected sensors, and try to put them
     * into the transmission queue in order to be sent over the air.
     */
    struct sensors_config_t sensors_cfg = {
        .device=BME280,
    };

    xTaskCreate(&setup_sensors, "setup_sensors", 2048, (void*) &sensors_cfg, 1,
            NULL);


    /* perform_transmissions will continuously get a reading from readings
     * transmission queue, format it and send it via one of the selected
     * application protocols (HTTP/MQTT/CoAP)
     */
    xTaskCreate(&perform_transmissions, "perform_transmissions", 4096, NULL, 1,
            NULL);

    while (1) {
        printf("main task is still running\n");
        vTaskDelay(10000/portTICK_PERIOD_MS);
    }

	return rc;
}
