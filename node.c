#include "contiki.h"
#include "net/tcpip.h"
#include "dev/leds.h"
#include "networking/networking.h"
#include "hw_module/sky.h"

struct template_rec *rec;

/*void read_temp(uint16_t* sens_val);
struct template_rec set_fields(uint8_t e_bit, uint16_t element_id,
		uint16_t field_len, uint32_t enterprise_id, void (*sens_val)(uint16_t*));

struct template_rec init_template() {

	rec = set_fields(E_BIT_TEMP, ELEMENT_ID_TEMP, LEN_TEMP, ENTERPRISE_ID_TEMP, &read_temp);

	return rec;
}

struct template_rec set_fields(uint8_t e_bit, uint16_t element_id,
		uint16_t field_len, uint32_t enterprise_id, void (*sens_val)(uint16_t*)) {

	struct template_rec rec;

	rec.element_id = element_id;
	rec.field_len = field_len;
	rec.enterprise_num = enterprise_id;

	if(e_bit == 1)
		rec.element_id |= 0x8000;

	rec.sens_val = sens_val;

	rec.dummy = 32;

	return rec;
}


void read_temp(uint16_t* sens_val) {

	//SENSORS_ACTIVATE(sht11_sensor);
	//*sens_val = sht11_sensor.value(SHT11_SENSOR_TEMP);
	//SENSORS_DEACTIVATE(sht11_sensor);

	*sens_val = 65535;
}*/


PROCESS(main_proc, "Main Process");
AUTOSTART_PROCESSES(&main_proc);




PROCESS_THREAD(main_proc, ev, data)
{
  // Process data declaration
  static struct etimer timer;


  uint32_t a;
  uint16_t b;

  PROCESS_BEGIN();

  rec = init_template();

  if(conn_set_up() == -1) {
	  PROCESS_EXIT();
  }

  // Set event timers for template and data packet creation
  etimer_set (&timer, CLOCK_SECOND * 5);

  while (1) {

	  PROCESS_WAIT_EVENT();
      if (etimer_expired (&timer)) {

    	  leds_on (LEDS_GREEN);
    	  clock_delay (500);

    	  leds_off (LEDS_GREEN);

    	  rec->sens_val(&b);
    	  //b = 65535;

    	  a=(uint32_t)b;
    	  send_data(&a);

    	  etimer_reset (&timer);
      }
  }

  PROCESS_END();
}


