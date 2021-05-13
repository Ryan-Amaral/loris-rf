#include "rf_send.h"



// Returns the index of the queue that will be used next for sending.
// -1 if nothing available to send.
uint8_t next_queue_index(const std::queue<rf::QueueItem> queues[], const uint8_t n_queues){
    for(int i=0; i<n_queues; ++i){
        if(queues[i].size() > 0){
            return i;
        }
    }

    return -1;
}

// Gets the next chunk of data from the queue_item, updates cursor.
uint8_t* get_chunk(rf::QueueItem* queue_item, uint32_t chunk_size){

    // if text data its simple

    // update cursor

    // call helper to get image data

    

    return nullptr;
}

// Opens and reads the image to get the chunk from it.
uint8_t* get_image_chunk(rf::QueueItem* queue_item, uint32_t chunk_size){

    // open image

    // start reading from cursor bit

    // read up to chunk size bites

    // update cursor

    return nullptr;
}

// Sends the chunk off to the low level sending firmware.
bool send_chunk(const uint8_t data[], const uint32_t length){
    // send data to lower level firmware
    // no idea what this looks like yet

    // return if successful
    return true;
}

// Gets the size in bytes of the image.
uint32_t get_image_size(const std::string image_path){
    return 500;
}


// Flag specifying whether we are in sending window.
bool rf::send_mode = false;

// Initializes the queues and establishes chunk size.
// Returns the queues and other data in a QueuesPackage.
// args: queue size, and chunk size.
rf::QueuesPackage* rf::init(const uint8_t n_queues, const uint32_t chunk_size){

    rf::QueuesPackage* qp = new rf::QueuesPackage;

    qp->queues = new std::queue<rf::QueueItem>[n_queues];
    qp->n_queues = n_queues;
    qp->chunk_size = chunk_size;
    qp->id_count = 0;

    return qp;
}

// Runs the loop for sending messages, ran in a pthread.
// args: QueuesPackage* as a void*.
void rf::send(void* vqp){

    rf::QueuesPackage* qp = (rf::QueuesPackage*)vqp;

    // enable send mode and run until stopped by module
    rf::send_mode = true;
    while(send_mode){
        // get a chunk of data from highest priority queue with data
        uint8_t queue_index = next_queue_index(qp->queues, qp->n_queues);
        // nothing available to send
        if(queue_index == -1){
            continue;
        }

        rf::QueueItem* queue_item = &qp->queues[queue_index].front();
        // save original cursor incase failure to send
        uint32_t o_cursor = queue_item->cursor;

        // chunk is an array of bytes (uint8_t's) to send
        uint8_t* chunk = get_chunk(queue_item, qp->chunk_size);
        // get size of the current chunk
        uint32_t cur_chunk_len = queue_item->cursor - o_cursor;

        // attempt to send that chunk synchronously, receiving success or failure
        bool success = send_chunk(chunk, cur_chunk_len);

        // reset cursor if send failed
        if(!success){
            queue_item->cursor = o_cursor;
        }

        // maybe notify someone of failure to send
        
        // pop if queue item totally done
        if(queue_item->cursor >= queue_item->n_bytes){
            qp->queues[queue_index].pop();
        }
    }
}

// Adds data to a queue of the specified type, data and priority.
// args: type, data, priority level, the queue
void rf::add_to_queue(const bool is_image, const std::string data, 
        uint8_t priority, rf::QueuesPackage* qp){

    // change improper priority value
    if(priority < 0){
        priority = 0;
    }
    else if(priority >= qp->n_queues){
        priority = qp->n_queues - 1;
    }

    // find the length of the data in bytes
    uint32_t n_bytes;
    if(is_image){
        n_bytes = get_image_size(data);
    }
    else{
        n_bytes = data.length();
    }

    // create the new queue item with cursor at 0
    qp->queues[priority].push(rf::QueueItem{is_image, 0, data, n_bytes, ++qp->id_count});
}

// Removes the front item from the given queue.
void rf::truncate_queue(rf::QueuesPackage* qp, const uint8_t priority){
    if(!qp->queues[priority].empty()){
        qp->queues[priority].pop();
    }
}

// Entirely empties a given queue.
void rf::empty_queue(rf::QueuesPackage* qp, const uint8_t priority){
    while(!qp->queues[priority].empty()){
        qp->queues[priority].pop();
    }
}

// Entirely empties all queues.
void rf::empty_queues(rf::QueuesPackage* qp){
    for(int i=0; i<qp->n_queues; ++i){
        while(!qp->queues[i].empty()){
            qp->queues[i].pop();
        }
    }
}

// Save the contents of queues to a file incase the system crashes.
// args: QueuesPackage* to save, string representing the file to save to.
void rf::save_queues(const rf::QueuesPackage*, const std::string){
    // todo implement
}

// Load a QueuesPackage* from the given file.
// args: string representing the file to load from.
rf::QueuesPackage* rf::load_queues(const std::string){
    // todo implement
    return nullptr;
}

// Deallocate any used dynamic memory.
// args: QueuesPackage* to have its contents deleted.
void rf::cleanup(rf::QueuesPackage* qp){
    delete[] qp->queues;
    delete qp;
}

/*int main(){
    rf_init(3, 10);
    return 0;
}*/