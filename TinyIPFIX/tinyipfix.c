#include "tinyipfix.h"
#include <stdint.h>

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

uint8_t buffer[MAX_MSG_SIZE];

/*
0                             1
0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
|E1|E2|    SetID  |        Length               |
|  |  |   Lookup  |                             |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
|   Sequence            |  Ext. Sequence        |
|    Number             |     Number            |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
| Ext. SetID            |
+--+--+--+--+--+--+--+--+
*/

build_msg_header() {



}

build_set_header() {

}

build_template_header() {


}


build_template_payload() {

}


build_data_payload() {


}
