#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"
#include "esp_heap_caps.h"
#include "bme280.h"

#include "sensor_reading.h"
#include "transmission.h"

#define DUMMY	-1

#define PIN_NUM_MISO DUMMY
#define PIN_NUM_MOSI DUMMY
#define PIN_NUM_CLK  DUMMY
#define PIN_NUM_CS   DUMMY

int8_t initialize_spi_communication();
int8_t initialize_i2c_communication();
int8_t initialize_bme_device(struct bme280_dev *dev);

/* fonctions de lecture et écriture via SPI */
int8_t read(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len);
int8_t write(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len);
void delay_ms(uint32_t period);

spi_device_handle_t spi;

/* définitions des fonctions */
int8_t
initialize_spi_communication()
{
    int8_t rc;

    spi_bus_config_t buscfg = {
		// failwith "Students, this is your job!
    };

    spi_device_interface_config_t devcfg={
		// failwith "Students, this is your job!
    };

    //Initialize the SPI bus
	// failwith "Students, this is your job!
    rc = ENOSYS;
    if (rc < 0) {
        printf("[IoT-Labs] Error while initializing SPI bus\n");
        return rc;
    }

    //Attach the device to the SPI bus
	// failwith "Students, this is your job!
    rc = ENOSYS;
    if (rc < 0) {
        printf("[IoT-Labs] Error while adding device to SPI bus\n");
        return rc;
    }

    return rc;
}

int8_t
initialize_i2c_communication()
{
    // failwith "Students, this is your job!
    int8_t rc;
    rc = ENOSYS;
    return rc;
}


int8_t
initialize_bme_device(struct bme280_dev *dev)
{
    int8_t rc;

	// Fill appropriate fields in bme280_dev structure
    dev->intf = BME280_SPI_INTF;
	// ...

    //Initialize the BME280
    rc = bme280_init(dev);
    printf("[initialize_bme_device] rc = %d\n", rc);
    if (rc < 0) {
        printf("[IoT-Labs] Error: bme280 device initialization failled\n");
        return rc;
    }

    return rc;
}

int8_t
read(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    int rc;
    static struct spi_transaction_t trans;

	// failwith "Students, this is your job!
	// fill spi_transaction_t structure with the right parameters
	// ...

	// failwith "Students, this is your job!
    rc = ENOSYS;
    if (rc < 0) {
        printf("[IoT-Labs] Error: transaction transmission failled\n");
        return rc;
    }

    memcpy(data, trans.rx_buffer, len);

    return rc;
}

int8_t
write(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    int8_t rc;
    static struct spi_transaction_t trans;

    trans.tx_buffer = heap_caps_malloc(len, MALLOC_CAP_DMA);
    // FIXME do we need to allocate memory for rx_buffer for write stub?
    trans.rx_buffer = heap_caps_malloc(len, MALLOC_CAP_DMA);

    trans.flags = 0;
    trans.addr = reg_addr;
    trans.length = len*8;

    memcpy(trans.tx_buffer, data, len);

    rc = spi_device_transmit(spi, &trans);
    if (rc < 0) {
        printf("[IoT-Labs] Error: transaction transmission failled\n");
        return rc;
    }

    return rc;
}

void
delay_ms(uint32_t period)
{
	vTaskDelay(period/portTICK_RATE_MS);
}

int8_t
_perform_sensor_readings(struct bme280_dev *dev, struct bme280_data *data)
{
    int8_t rc;

    // fake data
    data->temperature = rand();
    data->humidity = rand();
    data->pressure = rand();
    rc = 0; // everything is OK!

    /* debug */
    printf("temperature = %f DegC\n", (float)data->temperature/100);
    printf("humidity = %f %%RH\n", (float)data->humidity/1024);
    printf("pressure = %f Pa\n", (float)data->pressure/256);

    return rc;
}

void
perform_sensor_readings(void *pvParameters)
{
    int8_t rc;
    struct bme280_dev *dev;
    struct bme280_data *data;

    dev = (struct bme280_dev*) pvParameters;
    data = (struct bme280_data*) malloc(sizeof(struct bme280_data));

    while (1) {
        /* get sensor reading */
        rc = _perform_sensor_readings(dev, data);
        if (rc < 0) {
            printf("[IoT-Lab] Error while performing sensor\
                    readings\n");
            goto end;
        }

        vTaskDelay(1000/portTICK_RATE_MS);
    }

end:
    vTaskDelete(NULL);
}

void
setup_sensors(void *pvParameters)
{
    int8_t rc;
    struct sensors_config_t *cfg;
    cfg = (struct sensors_config_t*) pvParameters;

    // TODO iterate over provided devices, in case we implement multiple
    //      sensors handling!
    switch (cfg->device) {
        case BME280:
            rc = ENOSYS;
            if (rc < 0) {
                printf("[IoT-Labs] Error while initializing spi bus\n");
                break;
            }

            struct bme280_dev dev;
            rc = ENOSYS;
            if (rc < 0) {
                printf("[IoT-Labs] Error while initializing bme280\n");
                break;
            }

            /* each time a sensor is setup, trigger a sensor_readings task */
            xTaskCreate(&perform_sensor_readings, "bme280_readings", 2048,
                    (void*) &dev, 1, NULL);

            break;

        case DHT11:
            rc = ENOSYS;
            break;

        default:
            rc = ENOSYS;
            break;
    }

    vTaskDelete(NULL);
}
