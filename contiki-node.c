/**
 * \file contiki-node.c
 *
 * \brief This file implements the node processes responsible for
 * 	gathering sensor data, creating template and data packets
 * 	and send it over the wireless network.
 *
 * \author Michael Meister
 */

#include "contiki.h"
#include "net/tcpip.h"
#include "dev/leds.h"
#include "debug/debug.h"
#include "udp-client-process.h"

/*---------------------------------------------------------------------------*/
PROCESS(data_sampler_process, "Data sampler process");
PROCESS(udp_client_process, "UDP client process");
AUTOSTART_PROCESSES(&data_sampler_process, &udp_client_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(data_sampler_process, ev, data)
{
  // Process data declaration
  static struct etimer template_timer;
  static struct etimer data_timer;

  PROCESS_BEGIN();

  // Set event timers for template and data packet creation
  etimer_set (&template_timer, CLOCK_SECOND * 15);
  etimer_set (&data_timer, CLOCK_SECOND * 5);

  // initialize data samplers
//  init_data_samplers ();

  // initialize tiny ipfix protocol stack
  //tiny_ipfix_init ();

  // create and send first template at start up
  //create_template ();
  //net_finish_template (0);
  // post event to udp client (send template)
  process_post (&udp_client_process, PROCESS_EVENT_SEND_TEMPLATE, NULL);

  while (1)
    {
      PROCESS_WAIT_EVENT();
      if (etimer_expired (&data_timer))
	{
	  PRINTF("IPFIX: Data resend timer fired\n");
	  //create_data ();
	  // post event to udp client (send data)
	  process_post (&udp_client_process, PROCESS_EVENT_SEND_DATA, NULL);
	  etimer_reset (&data_timer);

	}
      if (etimer_expired (&template_timer))
	{
	  PRINTF("IPFIX: Template resend timer fired\n");
	  //net_finish_template (0);
	  // post event to udp client (send template)
	  process_post (&udp_client_process, PROCESS_EVENT_SEND_TEMPLATE, NULL);
	  etimer_reset (&template_timer);
	}
    }

PROCESS_END();
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(udp_client_process, ev, data)
{
  PROCESS_BEGIN();

  if (!setup_udp_connection ())
    {
      PROCESS_EXIT();
    }

  while (1)
    {
      PROCESS_WAIT_EVENT();
      if (ev == PROCESS_EVENT_SEND_DATA)
	{
	  PRINTF("UDP client invoked. Send data...\n");
	  //);

	  leds_on (LEDS_GREEN);
	  clock_delay (1000);
	  leds_off (LEDS_GREEN);
	}
      if (ev == PROCESS_EVENT_SEND_TEMPLATE)
	{
	  PRINTF("UDP client invoked. Send template...\n");
	  send_data_handler ();

	  leds_on (LEDS_RED);
	  clock_delay (1000);
	  leds_off (LEDS_RED);
	}
      if (ev == tcpip_event)
	{
	  PRINTF("UDP client invoked. Send received data...\n");
	  receive_data_handler ();
	}
    }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

