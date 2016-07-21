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


  while (1)
    {
      PROCESS_WAIT_EVENT();
      if (etimer_expired (&data_timer))
	{
	  //create_data ();
	  // post event to udp client (send data)
	  process_post (&udp_client_process, PROCESS_EVENT_SEND_DATA, NULL);
	  etimer_reset (&data_timer);

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
    	  send_data_handler ();

	  leds_on (LEDS_GREEN);
	  clock_delay (1000);
	  leds_off (LEDS_GREEN);
	}
    }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

