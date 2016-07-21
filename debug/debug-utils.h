/**
 * \file debug-utils.h
 *
 * \brief This file declares helper functions for debugging.
 *
 * \author Michael Meister
 */

#ifndef DEBUG_UTILS_H
#define DEBUG_UTILS_H

#include <stdint.h>

/**
 * \brief Print the contents of a byte array in hexadecimal notation.
 */
void dump_buffer(uint8_t *buffer, uint16_t buffer_size);

#endif /* DEBUG_UTILS_H */
