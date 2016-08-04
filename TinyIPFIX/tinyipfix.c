#include "tinyipfix.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//here comes the choosing of the sensor
#include "../hw_module/sky.h"

//maybe not needed
#ifndef EXTENDED_HEADER_SEQ
	#define EXTENDED_HEADER_SEQ 0
#endif
#ifndef EXTENDED_HEADER_SET_ID
	#define EXTENDED_HEADER_SET_ID 0
#endif
#if EXTENDED_HEADER_SET_ID == 1
	#if EXTENDED_HEADER_SEQ == 1
		#define MSG_HEADER_SIZE 5
	#else
		#define MSG_HEADER_SIZE 4
	#endif
#else
	#if EXTENDED_HEADER_SEQ == 1
		#define MSG_HEADER_SIZE 4
	#else
		#define MSG_HEADER_SIZE 3
	#endif
#endif

#define SWITCH_ENDIAN_16(n) (uint16_t)((((uint16_t) (n)) << 8) | (((uint16_t) (n)) >> 8))
#define SWITCH_ENDIAN_32(n) (((uint32_t)SWITCH_ENDIAN_16(n) << 16) | SWITCH_ENDIAN_16((uint32_t)(n) >> 16))

uint16_t build_msg_header(uint16_t set_id, uint16_t length, uint16_t seq_num);

void build_template(void);

void build_data_payload(void);
void build_data_header(void);

uint8_t template_buf[MAX_MSG_SIZE];

uint8_t data_buf[MAX_MSG_SIZE];

uint16_t data_tmp_len;
uint16_t data_seq_num = 0;

struct template_rec *sensor;
struct buf_info *instance;


void initialize(void) {

	int i;
	sensor = init_template();

	//fixed at compile time: template/data header and template payload, only do it once
	build_template(); //header and payload
	build_data_header();

}

uint16_t build_msg_header(uint16_t set_id, uint16_t length, uint16_t seq_num) {

	uint16_t header_len;

	//basic checks
	if(set_id > MAX_SET_ID || seq_num > MAX_SEQ_NUM || length > MAX_MSG_SIZE)
		return -1;

	//zeroing out, can't rely on zero in mem
	template_buf[0] = 0;

	if(set_id == TEMPLATE_SET_ID) {
		set_id = 1;
	} else if(set_id == DATA_SET_ID) {
		set_id = 2;
	}

	if(set_id < 16) {
		template_buf[0] |= (set_id << 2);
	}

	length += (3 + EXTENDED_HEADER_SET_ID + EXTENDED_HEADER_SEQ);
	template_buf[0] |= (uint8_t)(length >> 8);
	template_buf[1] = (uint8_t)(length);

	template_buf[2] = (uint8_t)(seq_num);

	if(EXTENDED_HEADER_SET_ID == 0 && EXTENDED_HEADER_SEQ == 0) {

	} else if(EXTENDED_HEADER_SET_ID == 0 && EXTENDED_HEADER_SEQ == 1) {

		template_buf[0] |= 0x40;
		template_buf[2] = (uint8_t)(seq_num >> 8);
		template_buf[3] = (uint8_t)(seq_num);
	} else if(EXTENDED_HEADER_SET_ID == 1 && EXTENDED_HEADER_SEQ == 0) {

		template_buf[0] |= 0x80;
		template_buf[0] |= ((set_id >> 8) << 2);
		template_buf[3] = (uint8_t)(set_id);

	} else {

		template_buf[0] |= 0xc0;

		template_buf[0] |= ((set_id >> 8) << 2);
		template_buf[4] = (uint8_t)(set_id);

		template_buf[2] = (uint8_t)(seq_num >> 8);
		template_buf[3] = (uint8_t)(seq_num);
	}

	header_len = 3;
	header_len += (EXTENDED_HEADER_SET_ID + EXTENDED_HEADER_SEQ);


	return header_len;
}

 void build_template(void) {

	uint8_t i;
	uint16_t element_id, field_len;
	uint32_t enterprise_num;

	uint16_t template_size = 0, template_tmp_len;

	//calculate length first to be able to build the message header
	for(i = 0; i < NUM_ENTRIES; i++) {

		if( ((sensor[i].element_id) | 0x8000) == sensor[i].element_id) {
			template_size += 4;
		}
	}

	template_size += 4*NUM_ENTRIES;

	template_tmp_len = build_msg_header(TEMPLATE_SET_ID, template_size, 0xFFFF);

	//get template length by counting fields with respect to set enterprise bit
	for(i = 0; i < NUM_ENTRIES; i++) {

		element_id = SWITCH_ENDIAN_16(sensor[i].element_id);
		memcpy(&template_buf[template_tmp_len], &element_id, sizeof(element_id));
		template_tmp_len += 2;

		field_len = SWITCH_ENDIAN_16(sensor[i].field_len);
		memcpy(&template_buf[template_tmp_len], &field_len, sizeof(field_len));
		template_tmp_len += 2;

		//check if E_BIT is set
		if( ((sensor[i].element_id) | 0x8000) == sensor[i].element_id) {

			enterprise_num = SWITCH_ENDIAN_32(sensor[i].enterprise_num);
			memcpy(&template_buf[template_tmp_len], &enterprise_num, sizeof(enterprise_num));
			template_tmp_len += 4;
		}
	}
}

void build_data_header(void) {

	uint8_t i;
	uint16_t data_size = 0;

	for(i = 0; i < NUM_ENTRIES; i++) {

		data_size += sensor[i].field_len;
	}

	data_tmp_len = build_msg_header(DATA_SET_ID, data_size, data_seq_num);

	uint8_t field[sensor[0].field_len];

	sensor[0].sens_val(field);



	printf("\n\n%d\n\n", *((uint16_t*)(field)));


}

void build_data_payload(void) {

}

uint8_t *get_template(void) {
	return template_buf;
}

uint8_t *get_data(void) {

	return data_buf;
}


