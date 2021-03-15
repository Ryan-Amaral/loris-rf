/*
rf_send.h

purpose: A continually running server for sending images and other messages
down to the ground station, based on multiple queues based on priority.
Simply sits idly by until told it is able to send stuff.
*/

#ifndef CUBESAT_RF_SEND_H
#define CUBESAT_RF_SEND_H

#include <string>
#include <queue>

struct QueueItem{
    // whether the item is an image or simple text data
    bool isImage;
    // what byte we are on in the message
    int cursor;
    // name of file if image item, otherwise the literal message to send
    std::string data;
};

// Initialize and runs the sending server.
// args: nQueues, chunkSize
void InitRfSend(const uint8_t, const uint32_t);

// Send the provided chunk of data.
// args: data (bytes), length of bytes array
bool SendChunk(const uint8_t&, const uint32_t);

// Adds data to a queue of the specified type, data and priority.
// args: type, data, priority level
void AddToQueue(bool, std::string, const uint8_t, std::queue<QueueItem>[]);

#endif