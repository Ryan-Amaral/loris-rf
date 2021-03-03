/*
Random notes up heres
*/

struct ImageHandler{
    int imageCursor; // byte or bit position in image
};

struct MessageQueue{
    int nMessages; // number of messages in the queue
    struct ImageHandler* imageHandler;
};