/**
 * \file debug-utils.c
 *
 * \brief This file implements helper functions for debugging.
 *
 * \author Michael Meister
 */

#include <stdio.h>
#include "debug-utils.h"

void
dump_buffer (uint8_t *buffer, uint16_t buffer_size)
{
  // hexadecimal char buffer
  uint8_t char_arr[buffer_size * 2 + (buffer_size / 8) * 2 + (buffer_size / 4) + 2];
  uint8_t i = 0;
  uint8_t j = 0;
  uint8_t halfbyte = 0;

  for (i = 0; i < buffer_size; i++)
    {
      if (i % 8 == 0)
	{
	  char_arr[j] = 13;
	  j++;
	  char_arr[j] = 10;
	  j++;
	}
      else if (i % 4 == 0)
	{
	  char_arr[j] = ' ';
	  j++;
	}

      halfbyte = (buffer[i] >> 4);
      if (halfbyte == 0) char_arr[j] = '0';
      else if (halfbyte == 1) char_arr[j] = '1';
      else if (halfbyte == 2) char_arr[j] = '2';
      else if (halfbyte == 3) char_arr[j] = '3';
      else if (halfbyte == 4) char_arr[j] = '4';
      else if (halfbyte == 5) char_arr[j] = '5';
      else if (halfbyte == 6) char_arr[j] = '6';
      else if (halfbyte == 7) char_arr[j] = '7';
      else if (halfbyte == 8) char_arr[j] = '8';
      else if (halfbyte == 9) char_arr[j] = '9';
      else if (halfbyte == 10) char_arr[j] = 'A';
      else if (halfbyte == 11) char_arr[j] = 'B';
      else if (halfbyte == 12) char_arr[j] = 'C';
      else if (halfbyte == 13) char_arr[j] = 'D';
      else if (halfbyte == 14) char_arr[j] = 'E';
      else if (halfbyte == 15) char_arr[j] = 'F';
      j++;

      halfbyte = ((uint8_t) (buffer[i] << 4) >> 4);
      if (halfbyte == 0) char_arr[j] = '0';
      else if (halfbyte == 1) char_arr[j] = '1';
      else if (halfbyte == 2) char_arr[j] = '2';
      else if (halfbyte == 3) char_arr[j] = '3';
      else if (halfbyte == 4) char_arr[j] = '4';
      else if (halfbyte == 5) char_arr[j] = '5';
      else if (halfbyte == 6) char_arr[j] = '6';
      else if (halfbyte == 7) char_arr[j] = '7';
      else if (halfbyte == 8) char_arr[j] = '8';
      else if (halfbyte == 9) char_arr[j] = '9';
      else if (halfbyte == 10) char_arr[j] = 'A';
      else if (halfbyte == 11) char_arr[j] = 'B';
      else if (halfbyte == 12) char_arr[j] = 'C';
      else if (halfbyte == 13) char_arr[j] = 'D';
      else if (halfbyte == 14) char_arr[j] = 'E';
      else if (halfbyte == 15) char_arr[j] = 'F';
      j++;
    }
  char_arr[j] = 0;
  printf ("DEBUG_DUMP: %s\n", char_arr);
}
