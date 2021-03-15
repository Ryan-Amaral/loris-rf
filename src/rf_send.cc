#include "rf_send.h"

void InitRfSend(const uint8_t nQueues, const uint32_t chunkSz){

    // initialize constantly needed items
    std::queue<QueueItem>* queues = new std::queue<QueueItem>[nQueues];
    uint32_t chunkSize = chunkSz;

    // boolean signifying whether we are in sending window
    bool sendingEh = false;

    // run indefinitely
    while(false){

        // check for diagnostics requests

        // check for param updates / resets / shutdown

        // check for queueing request

        // check for if sending mode

        // send if right mode
        if(sendingEh){
            // get a chunk of data from highest priority queue with data

            // attempt to send that chunk synchronously, receiving success or failure
            //bool success = SendChunk

            // update cursor if chunk send success, or pop if sent all data
        }
    }


    // temp test stuff here:
    printf("%ld\n", queues[0].size());
    printf("%ld\n", queues[1].size());
    printf("%ld\n", queues[2].size());

    AddToQueue(false, "hallooo", 2, queues);
    AddToQueue(true, "dir/file.png", 0, queues);
    
    printf("%ld\n", queues[0].size());
    printf("%ld\n", queues[1].size());
    printf("%ld\n", queues[2].size());


    printf("%s\n", queues[0].front().data.c_str());
    printf("%s\n", queues[2].front().data.c_str());


    delete[] queues;
}

bool SendChunk(const uint8_t& data, const uint32_t length){
    // send data to antenna firmware
    // no idea what this looks like yet

    // return if successful
    return true;
}

void AddToQueue(bool isImage, std::string data, const uint8_t priority, std::queue<QueueItem> queues[]){
    try{
        // create the new queue item with cursor at 0
        queues[priority].push(QueueItem{isImage, 0, data});
    }catch(...){
        // priority probably out of range
        
    }
}

int main(){
    InitRfSend(3, 10);
    return 0;
}