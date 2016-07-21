#include "contiki.h"
#include "net/tcpip.h"
#include "dev/leds.h"
#include "networking/networking.h"

/*---------------------------------------------------------------------------*/
PROCESS(data_sampler_process, "Data sampler process");
PROCESS(udp_client_process, "UDP client process");
AUTOSTART_PROCESSES(&data_sampler_process, &udp_client_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(data_sampler_process, ev, data)
{
  // Process data declaration
  static struct etimer data_timer;

  PROCESS_BEGIN();

  // Set event timers for template and data packet creation
  etimer_set (&data_timer, CLOCK_SECOND * 5);


  while (1)
    {
      PROCESS_WAIT_EVENT();
      if (etimer_expired (&data_timer))
	{
    	  leds_on (LEDS_GREEN);
    	  	  clock_delay (1000);
    	  	  leds_off (LEDS_GREEN);

    	  send_data();
	  etimer_reset (&data_timer);

	}
    }

PROCESS_END();
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(udp_client_process, ev, data)
{
  PROCESS_BEGIN();

  if (conn_set_up() == -1)
    {
      PROCESS_EXIT();
    }


  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

