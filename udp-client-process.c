#include "sys/node-id.h"
#include "net/uip.h"
#include "net/uip-udp-packet.h"
#include "udp-client-process.h"

/*---------------------------------------------------------------------------*/

static struct uip_udp_conn* client_conn;
static uip_ipaddr_t server_ipaddr;

/*---------------------------------------------------------------------------*/
bool
setup_udp_connection ()
{
  // IP address of the border router
  uip_ip6addr(&server_ipaddr, 0xaaaa, 0, 0, 0, 0x0250, 0xc2ff, 0xfea8, 0xcd1a);

  

  // create UDP connection
  client_conn = udp_new (&server_ipaddr, UIP_HTONS (UDP_SERVER_PORT), NULL);
  if (client_conn == NULL)
    {
      return false;
    }
  udp_bind(client_conn, UIP_HTONS (UDP_CLIENT_PORT));

  return true;
}
/*---------------------------------------------------------------------------*/
void
send_data_handler ()
{
  int i;
  char buf[50];

  for(i = 0; i < 50; i++) {
    buf[i] = 'r';
  }

  uip_udp_packet_send(client_conn, buf, 50);

  //uip_udp_packet_send (client_conn, data, length);
  //uip_udp_packet_send (client_conn, data, length);
}
/*---------------------------------------------------------------------------*/
void
receive_data_handler ()
{
  if (uip_newdata ())
    {
      send_data_handler (uip_appdata, uip_datalen());
    }
}
/*---------------------------------------------------------------------------*/
