/*
rf_send.h

Purpose: A continually running server for sending images and other messages
down to the ground station, based on multiple queues based on priority.
Simply sits idly by until told it is able to send stuff.

Author: Ryan Amaral
*/

#ifndef CUBESAT_RF_SEND_H
#define CUBESAT_RF_SEND_H

#include <string>
#include <queue>

struct QueueItem{
    // whether the item is an image or simple text data
    bool is_image;
    // what byte we are on in the message
    uint32_t cursor;
    // name of file if image item, otherwise the literal message to send
    std::string data;
    // number of bytes in the item
    uint32_t n_bytes;
};



// flag specifying whether we are in sending window
extern bool send_mode;



// array of queues of different priorities
extern std::queue<QueueItem>* g_queues;
// track size of the array
extern uint8_t g_n_queues;
// size of chunks for sending data
extern uint32_t g_chunk_size;



// Initializes the queues and establishes chunk size.
void rf_init(const uint8_t, const uint32_t);

// Runs the loop for sending messages.
// args: nQueues, chunkSize
void rf_send();

// Adds data to a queue of the specified type, data and priority.
// Gives error code: 0 success, 1 too low, 2 too high.
// args: type, data, priority level, the queue
void rf_add_to_queue(const bool, const std::string, uint8_t);

#endif