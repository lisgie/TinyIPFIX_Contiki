#include "networking.h"
#include "net/uip.h"
#include "net/uip-udp-packet.h"

static struct uip_udp_conn* conn_handle;
static uip_ipaddr_t border_router;

int conn_set_up() {

	uip_ip6addr(&border_router, 0xaaaa, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff);

	if((conn_handle = udp_new (&border_router, UIP_HTONS (BORDER_ROUTER_PORT), NULL)) == NULL)
		return -1;

	udp_bind(conn_handle, UIP_HTONS (NODE_PORT));

	return 0;
}

void send_data(void *data) {

	uint8_t a[4];
	uint32_t len = 4;

	*((uint32_t*)(a)) = *((uint32_t*)(data));

	uip_udp_packet_send(conn_handle, a, len);
}
