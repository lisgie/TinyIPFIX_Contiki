#include "contiki.h"
#include "net/tcpip.h"
#include "dev/leds.h"
#include "networking/networking.h"

PROCESS(main_proc, "Main Process");
AUTOSTART_PROCESSES(&main_proc);

PROCESS_THREAD(main_proc, ev, data)
{
  // Process data declaration
  static struct etimer timer;

  PROCESS_BEGIN();

  if(conn_set_up() == -1) {
	  PROCESS_EXIT();
  }

  // Set event timers for template and data packet creation
  etimer_set (&timer, CLOCK_SECOND * 2);

  while (1) {

	  PROCESS_WAIT_EVENT();
      if (etimer_expired (&timer)) {

    	  leds_on (LEDS_GREEN);
    	  clock_delay (500);
    	  leds_off (LEDS_GREEN);
    	  send_data();
    	  etimer_reset (&timer);
      }
  }

  PROCESS_END();
}
