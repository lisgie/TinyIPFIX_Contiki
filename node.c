#include "contiki.h"
#include "net/tcpip.h"
#include "dev/leds.h"
#include "networking/networking.h"
#include "hw_module/sky.h"

#include "TinyIPFIX/tinyipfix.h"

struct template_rec *sky_rec;

PROCESS(main_proc, "Main Process");
AUTOSTART_PROCESSES(&main_proc);

PROCESS_THREAD(main_proc, ev, data)
{
  // Process data declaration
  static struct etimer timer;

  uint8_t payload[6];

  PROCESS_BEGIN();

  sky_rec = init_template();

  if(conn_set_up() == -1) {
	  PROCESS_EXIT();
  }

  // Set event timers for template and data packet creation
  etimer_set (&timer, CLOCK_SECOND * 5);

  while (1) {

	  PROCESS_WAIT_EVENT();
      if (etimer_expired (&timer)) {

    	  sky_rec[0].sens_val(&payload[0]);
    	  sky_rec[1].sens_val(&payload[2]);
    	  sky_rec[2].sens_val(&payload[4]);

    	  leds_on (LEDS_GREEN);
    	  clock_delay (500);
    	  leds_off (LEDS_GREEN);

    	  send_data(payload, 6);

    	  etimer_reset (&timer);
      }
  }

  PROCESS_END();
}


