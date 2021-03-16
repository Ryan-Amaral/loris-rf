#include "rf_send.h"

// give concrete definition to external variables
std::string e_data;
int e_priority;
bool add_text_to_queue;
bool add_image_to_queue;
bool send_mode;


void rf_init(const uint8_t n_queues, const uint32_t chunk_sz){
    // set up the queues, and chunk size for sending
    queues = new std::queue<QueueItem>[n_queues];
    num_queues = n_queues;
    chunk_size = chunk_sz;

    // initialize flags
    add_text_to_queue = false;
    add_image_to_queue = false;
    //send_mode = false;

    printf("%d", send_mode);
}

void rf_send(const uint8_t nQueues, const uint32_t chunkSz){

    // initialize constantly needed items
    std::queue<QueueItem>* queues = new std::queue<QueueItem>[nQueues];
    uint32_t chunkSize = chunkSz;

    // run indefinitely
    while(false){

        // check for diagnostics requests

        // check for param updates / resets / shutdown

        // check for queueing request
        if(add_text_to_queue){
            rf_add_to_queue(false, e_data, e_priority, queues);
            add_text_to_queue = false;
        }
        else if(add_image_to_queue){
            rf_add_to_queue(true, e_data, e_priority, queues);
            add_image_to_queue = true;
        }

        // check for if sending mode

        // send if right mode
        if(send_mode){
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

    rf_add_to_queue(false, "hallooo", 2, queues);
    rf_add_to_queue(true, "dir/file.png", 0, queues);
    rf_add_to_queue(true, "dir/file2.png", 0, queues);
    
    printf("%ld\n", queues[0].size());
    printf("%ld\n", queues[1].size());
    printf("%ld\n", queues[2].size());


    printf("%s\n", queues[0].front().data.c_str());
    printf("%s\n", queues[0].back().data.c_str());
    printf("%s\n", queues[2].front().data.c_str());


    delete[] queues;
}

bool rf_send_chunk(const uint8_t& data, const uint32_t length){
    // send data to lower level firmware
    // no idea what this looks like yet

    // return if successful
    return true;
}

void rf_add_to_queue(const bool is_image, const std::string data, uint8_t priority, std::queue<QueueItem> queues[]){

    // change improper priority value
    if(priority < 0){
        priority = 0;
    }
    else if(priority >= num_queues){
        priority = num_queues - 1;
    }

    // create the new queue item with cursor at 0
    queues[priority].push(QueueItem{is_image, 0, data});
}

/*int main(){
    rf_init(3, 10);
    return 0;
}*/