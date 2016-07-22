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

void send_data() {
	int i;
	char buf[50];

	for(i = 0; i < 50; i++) {
		buf[i] = 'r';
	}

	uip_udp_packet_send(conn_handle, buf, 50);
}
