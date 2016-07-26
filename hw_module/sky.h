#ifndef SKY_H_
#define SKY_H_

#define NUM_SENSORS 3

//SHT11 Temperatur Sensor
#define ELEMENT_ID_TEMP 0x80A0
#define ENTERPRISE_ID_TEMP 0xF0AA00AA
#define E_BIT_TEMP 1
#define LEN_TEMP 2

//SHT11 Humidity Sensor
#define ELEMENT_ID_HUMID 0x80A1
#define ENTERPRISE_ID_HUMID 0xF0AA00AA
#define E_BIT_HUMID 1
#define LEN_HUMID 2

//S1087-01 Light Sensor
#define ELEMENT_ID_LIGHT 0x80A3
#define ENTERPRISE_ID_LIGHT 0xF0AA00AA
#define E_BIT_LIGHT 1
#define LEN_LIGHT 2

struct template_rec {

	//the enterprise bit will be the MSB of element_id, to not waste another byte
	uint16_t element_id;
	uint16_t field_len;
	uint32_t enterprise_num;

	void (* sens_val)(uint16_t*);
};


//needs to be accessible from outside
struct template_rec init_template();



#endif /* SKY_H_ */
