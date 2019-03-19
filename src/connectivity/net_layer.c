#include <errno.h>

#include "phy_layer.h"
#include "net_layer.h"

#include "tcpip_adapter.h"

int8_t
setup_ipv4(void)
{
    int8_t rc;
    tcpip_adapter_ip_info_t ip_info;

    // wait for connection
    printf("[IoT-Labs] Waiting for connection to the wifi network... \n");
    xEventGroupWaitBits(wifi_event_group, IPv4_CONNECTED_BIT, false, true,
            portMAX_DELAY);
    printf("[IoT-Labs] connected!\n");
    
    // print the local IP address
    rc = tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ip_info);
    if (rc < 0) {
        printf("[IoT-Labs] Error while getting ip information\n");
        return rc;
    }
    
    printf("[IoT-Labs] IP Address:  %s\n", ip4addr_ntoa(&ip_info.ip));
    printf("[IoT-Labs] Subnet mask: %s\n", ip4addr_ntoa(&ip_info.netmask));
    printf("[IoT-Labs] Gateway:     %s\n", ip4addr_ntoa(&ip_info.gw));

    return rc;
}

int8_t
network_layer_start(enum net_protocols net_proto)
{
    int8_t rc;

    switch (net_proto) {
        case IPv4:
            rc = setup_ipv4();
            if (rc < 0) {
                printf("[IoT-Labs]");
                return rc;
            }
            break;

        case IPv6:
            // TODO consider using the following function call in order to use IPv6:
            //      `tcpip_adapter_create_ip6_linklocal()`
            rc = ENOSYS;
            break;

        case _6LowPAN:
            // FIXME BLE would work only with 6LowPAN over it. Any other combination
            //       has to throw an exception
            // TODO take a look at
            // http://git.savannah.nongnu.org/cgit/lwip.git/tree/src/include/netif/lowpan6_ble.h
            rc = ENOSYS;
            break;

        default:
            rc = ENOSYS;
            break;
    }

    return rc;
}


