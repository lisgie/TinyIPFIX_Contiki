/**
 * \file udp-client-process.h
 *
 * \brief This file declares functions used by the UDP client process,
 * 	responsible for setting up the UDP connection and sending TinyIPFIX packets.
 *
 * \author Michael Meister
 */

#ifndef UDP_CLIENT_PROCESS_H
#define UDP_CLIENT_PROCESS_H

#define PROCESS_EVENT_SEND_TEMPLATE 10
#define PROCESS_EVENT_SEND_DATA 11

#define UDP_CLIENT_PORT 10000
#define UDP_SERVER_PORT 10000

#include "stdbool.h"
#include <stdint.h>

/**
 * \brief Initialize UDP connection and IP addresses.
 */
bool setup_udp_connection ();

/**
 * \brief Send data over UDP connection.
 */
void send_data_handler ();

/**
 * \brief Receive data over UDP connection.
 */
void receive_data_handler ();

#endif /* UDP_CLIENT_PROCESS_H */
