#include "rf_send.h"

// give concrete definition to external data and flags
// external flag for when we are in send mode
bool send_mode = false;

// give concrete definition to important global variables
// globally accessible queues
std::queue<QueueItem>* g_queues;
// globally accessible lengh of queues
uint8_t g_n_queues = 0;
// globablly accessible chunk size
uint32_t g_chunk_size = 0;

void rf_init(const uint8_t n_queues, const uint32_t chunk_size){
    // set up the queues, and chunk size for sending
    g_queues = new std::queue<QueueItem>[n_queues];
    g_n_queues = n_queues;
    g_chunk_size = chunk_size;
}

void rf_send(){

    // enable send mode and run until stopped by module
    send_mode = true;
    while(send_mode){
        // get a chunk of data from highest priority queue with data
        uint8_t queue_index = next_queue_index();
        QueueItem* queue_item = &g_queues[queue_index].front();
        uint8_t* chunk = get_chunk(queue_item);

        // attempt to send that chunk synchronously, receiving success or failure
        //bool success = rf_send_chunk()
        
        // pop if queue item totally done
        if(queue_item->cursor >= queue_item->n_bytes){
            g_queues[queue_index].pop();
        }
    }
}

// Returns the index of the queue that will be used next for sending.
// -1 if nothing available to send.
uint8_t next_queue_index(){
    for(int i=0; i<g_n_queues; ++i){
        if(g_queues[i].size() > 0){
            return i;
        }
    }

    return -1;
}

// Returns the index of the queue that will be used next for sending.
// -1 if nothing available to send.
QueueItem* next_queue_item(){
    for(int i=0; i<g_n_queues; ++i){
        if(g_queues[i].size() > 0){
            return &g_queues[i].front();
        }
    }

    return nullptr;
}

uint8_t* get_chunk(QueueItem* queue_item){

    // find the highest priority queue with an item
    

    // get the next chunk from that item

    

    return nullptr;
}

bool send_chunk(const uint8_t data[], const uint32_t length){
    // send data to lower level firmware
    // no idea what this looks like yet

    // return if successful
    return true;
}

void rf_add_to_queue(const bool is_image, const std::string data, uint8_t priority){

    // change improper priority value
    if(priority < 0){
        priority = 0;
    }
    else if(priority >= g_n_queues){
        priority = g_n_queues - 1;
    }

    // find the length of the data in bytes
    // todo: create a function for this
    uint32_t n_bytes = 500;

    // create the new queue item with cursor at 0
    g_queues[priority].push(QueueItem{is_image, 0, data, n_bytes});
}

/*int main(){
    rf_init(3, 10);
    return 0;
}*/