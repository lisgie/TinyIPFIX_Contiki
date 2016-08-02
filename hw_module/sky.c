#include <stdint.h>
#include "sky.h"
#include "dev/sht11-sensor.h"
#include "dev/light-sensor.h"


struct template_rec set_fields(uint8_t, uint16_t, uint16_t, uint32_t, void(*sens_val)(void*));
void read_temp(void*);
void read_humid(void*);
void read_light(void*);

struct template_rec sky_rec[NUM_SENSORS];

struct template_rec *init_template() {

	sky_rec[0] = set_fields(E_BIT_TEMP, ELEMENT_ID_TEMP, LEN_TEMP, ENTERPRISE_ID_TEMP, &read_temp);
	sky_rec[1] = set_fields(E_BIT_HUMID, ELEMENT_ID_HUMID, LEN_HUMID, ENTERPRISE_ID_HUMID,&read_humid);
	sky_rec[2] = set_fields(E_BIT_LIGHT, ELEMENT_ID_LIGHT, LEN_LIGHT, ENTERPRISE_ID_LIGHT,&read_light);

	return sky_rec;
}

struct template_rec set_fields(uint8_t e_bit, uint16_t element_id,
		uint16_t field_len, uint32_t enterprise_id, void (*sens_val)(void*)) {

	struct template_rec rec;

	rec.element_id = element_id;
	rec.field_len = field_len;
	rec.enterprise_num = enterprise_id;

	if(e_bit == 1)
		rec.element_id |= 0x8000;

	rec.sens_val = sens_val;

	return rec;
}

void read_temp(void* temp) {

	SENSORS_ACTIVATE(sht11_sensor);
	*((uint16_t*)(temp)) = sht11_sensor.value(SHT11_SENSOR_TEMP);
	SENSORS_DEACTIVATE(sht11_sensor);

}

void read_humid(void* humid) {

	SENSORS_ACTIVATE(sht11_sensor);
	*((uint16_t*)(humid)) = sht11_sensor.value(SHT11_SENSOR_HUMIDITY);
	SENSORS_DEACTIVATE(sht11_sensor);
}

void read_light (void* light_photo) {

	SENSORS_ACTIVATE(light_sensor);
	(*((uint16_t*)(light_photo))) = light_sensor.value(LIGHT_SENSOR_PHOTOSYNTHETIC);
	SENSORS_DEACTIVATE(light_sensor);
}

