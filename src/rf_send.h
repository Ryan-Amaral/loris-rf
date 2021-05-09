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

// Each individual item in a queue.
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

// Package to send to rf_send functions to have all queue data.
struct SendQueuesPackage{
    // The different queues representing different priorities.
    std::queue<QueueItem>* queues;
    // The number of queues.
    int n_queues;
    // Size of chunks to send to ground station.
    int chunk_size;
};

// flag specifying whether we are in sending window
extern bool send_mode;

// Initializes the queues and establishes chunk size.
void rf_init(const uint8_t, const uint32_t);

// Runs the loop for sending messages, ran in a pthread.
void rf_send(void*);

// Adds data to a queue of the specified type, data and priority.
// Gives error code: 0 success, 1 too low, 2 too high.
// args: type, data, priority level, the queue
void rf_add_to_queue(const bool, const std::string, uint8_t);

// Deallocate any used dynamic memory.
void cleanup();

#endif