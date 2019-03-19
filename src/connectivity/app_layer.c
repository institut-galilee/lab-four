#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "app_layer.h"
#include "trans_layer.h"

#define REQUEST_SIZE_MAX    200

char hostname[] = "hostname";
char resource[] = "/resource";

// TODO probably introducing an encryption layer on top of the application
// protocol (application layer encryption). This has not to be confused with
// transport layer encryption like tls which lie on top of the transport
// layer.

int8_t app_layer_start(enum app_protocols app_proto);
int8_t send_a_reading(const char *formatted_reading);
int8_t http_send(const char *formatted_reading);
int8_t coap_send(const char *formatted_reading);
int8_t mqtt_send(const char *formatted_reading);

int8_t
application_layer_start(enum app_protocols app_proto)
{
    int8_t rc;

    switch (app_proto) {
        case HTTP:
            rc = ENOSYS;
            break;
        case CoAP:
            rc = ENOSYS;
            break;
        case MQTT:
            rc = ENOSYS;
            break;
        default:
            rc = ENOSYS;
            break;
    }

    return rc;
}

int8_t
send_a_reading(const char *formatted_reading)
{
    int8_t rc;

    // TODO switch between available protocols

    rc = http_send(formatted_reading);
    if (rc < 0) {
        printf("[IoT-Labs] Error while sending a reading over http\n");
        return rc;
    }

    return rc;
}

int8_t
http_send(const char *formatted_reading)
{
    int8_t rc;
    char *sendline;

    sendline = (char*)malloc(REQUEST_SIZE_MAX*sizeof(char));
    if (sendline == NULL) {
        printf("[IoT-Labs] Error while allocating memory for http request\n");
        return errno;
    }

    /* wrap formatted_reading with an HTTP request, ... */
    rc = ENOSYS; 

    /* ... then send it via transport layer */
    rc = ENOSYS;

    return rc;
}

int8_t
coap_send(const char *formatted_reading)
{
    // failwith "Students, this is your job!"
    int8_t rc;
    rc = ENOSYS;

    return rc;
}

int8_t
mqtt_send(const char *formatted_reading)
{
    // failwith "Students, this is your job!"
    int8_t rc;
    rc = ENOSYS;

    return rc;
}
