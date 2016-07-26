#include "contiki.h"
#include "net/tcpip.h"
#include "dev/leds.h"
#include "networking/networking.h"
#include "hw_module/sky.h"

PROCESS(main_proc, "Main Process");
AUTOSTART_PROCESSES(&main_proc);

PROCESS_THREAD(main_proc, ev, data)
{
  // Process data declaration
  static struct etimer timer;
  struct template_rec record;

  char *garbage = "asdkfjlwke jf wkdjl ksjd kwlke lksd lwke lksjk ";

  PROCESS_BEGIN();

  record = init_template();


  if(conn_set_up() == -1) {
	  PROCESS_EXIT();
  }

  // Set event timers for template and data packet creation
  etimer_set (&timer, CLOCK_SECOND * 3);

  while (1) {

	  PROCESS_WAIT_EVENT();
      if (etimer_expired (&timer)) {

    	  uint16_t a;
    	  leds_on (LEDS_GREEN);
    	  clock_delay (500);
    	  leds_off (LEDS_GREEN);
    	  //record.sens_val(&a);
    	  send_data(23);
    	  etimer_reset (&timer);
      }
  }

  PROCESS_END();
}
