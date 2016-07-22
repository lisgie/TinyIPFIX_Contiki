#include <stdint.h>
#include "sky.h"
#include "dev/sht11-sensor.h"

struct template_rec set_fields(uint8_t e_bit, uint16_t element_id,
		uint16_t field_len, uint32_t enterprise_id, uint16_t* (*sens_val)(void));
uint16_t* read_temp(void);

struct template_rec {

	//the enterprise bit will be the MSB of element_id, to not waste another byte
	uint16_t element_id;
	uint16_t field_len;
	uint32_t enterprise_num;

	uint16_t* (* sens_val)(void);
};

struct template_rec record[NUM_SENSORS];

void init_template() {

	record[0] = set_fields(E_BIT_TEMP, ELEMENT_ID_TEMP, LEN_TEMP, ENTERPRISE_ID_TEMP, &read_temp);
	//record[1] = set_fields(E_BIT_HUMID, ELEMENT_ID_HUMID, LEN_HUMID, ENTERPRISE_ID_HUMID,&dummy);
	//record[2] = set_fields(E_BIT_LIGHT, ELEMENT_ID_LIGHT, LEN_LIGHT, ENTERPRISE_ID_LIGHT,&dummy);
}


struct template_rec set_fields(uint8_t e_bit, uint16_t element_id,
		uint16_t field_len, uint32_t enterprise_id, uint16_t* (*sens_val)(void)) {

	struct template_rec rec;

	rec.element_id = element_id;
	rec.field_len = field_len;
	rec.enterprise_num = enterprise_id;

	if(e_bit == 1)
		rec.element_id |= 0x8000;

	return rec;
}

uint16_t* read_temp(void) {

	uint16_t sens_val;

	SENSORS_ACTIVATE(sht11_sensor);
	sens_val = sht11_sensor.value(SHT11_SENSOR_TEMP);
	SENSORS_DEACTIVATE(sht11_sensor);

	return &sens_val;
}


