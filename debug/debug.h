/**
 * \file debug.h
 *
 * \brief This file defines debugging functions in case that debugging is enabled.
 *
 * \author Michael Meister
 */

#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG 0
#if DEBUG
  #include <stdio.h>
  #include "debug-utils.h"
  #define PRINTF(...) printf(__VA_ARGS__)
  #define PRINT6ADDR(addr) PRINTF("%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x ", ((u8_t *)addr)[0], ((u8_t *)addr)[1], ((u8_t *)addr)[2], ((u8_t *)addr)[3], ((u8_t *)addr)[4], ((u8_t *)addr)[5], ((u8_t *)addr)[6], ((u8_t *)addr)[7], ((u8_t *)addr)[8], ((u8_t *)addr)[9], ((u8_t *)addr)[10], ((u8_t *)addr)[11], ((u8_t *)addr)[12], ((u8_t *)addr)[13], ((u8_t *)addr)[14], ((u8_t *)addr)[15])
  #define PRINTLLADDR(lladdr) PRINTF(" %02x:%02x:%02x:%02x:%02x:%02x ",(lladdr)->addr[0], (lladdr)->addr[1], (lladdr)->addr[2], (lladdr)->addr[3],(lladdr)->addr[4], (lladdr)->addr[5])
  #define DUMP_BUFFER(buffer, buffer_size) dump_buffer(buffer, buffer_size)
#else
  #define PRINTF(...)
  #define PRINT6ADDR(addr)
  #define PRINTLLADDR(addr)
  #define DUMP_BUFFER(buffer, buffer_size)
#endif

#endif /* DEBUG_H */
