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
    int cursor;
    // name of file if image item, otherwise the literal message to send
    std::string data;
};




// variables for transferring message info to the thread this runs on
extern std::string e_data;
extern int e_priority;

// flags for adding stuff to queue
extern bool add_text_to_queue;
extern bool add_image_to_queue;
// boolean signifying whether we are in sending window
extern bool send_mode;




// array of queues of different priorities
static std::queue<QueueItem>* queues;
// track size of the array
static uint8_t num_queues;
// size of chunks for sending data
static uint32_t chunk_size;




// Initializes the queues and establishes chunk size.
void rf_init(const uint8_t, const uint32_t);

// Runs the loop for sending messages.
// args: nQueues, chunkSize
void rf_send();

// Send the provided chunk of data.
// args: data (bytes), length of bytes array
bool rf_send_chunk(const uint8_t&, const uint32_t);

// Adds data to a queue of the specified type, data and priority.
// Gives error code: 0 success, 1 too low, 2 too high.
// args: type, data, priority level, the queue
void rf_add_to_queue(const bool, const std::string, uint8_t, std::queue<QueueItem>[]);

#endif