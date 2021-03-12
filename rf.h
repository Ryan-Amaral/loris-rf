#ifndef RF_HEADER
#define HEADER

#include <stdbool.h>
#include <string.h>

// contains file name and byte possition in image for sending
struct ImageSendData{
    char* fName;
    int pos;
};

// info for each item to send
struct SendJobData{
    jobDataType jdt;
    char* msg;
    ImageSendData isd;
};

// bool for receiving loop incase gracefull shutdown needed
bool doReceive = true;

struct ImageHandler{
    // byte or bit position in image
    int imageCursor;
};

struct MessageQueue{
    int nMessages; // number of messages in the queue
    struct ImageHandler* imageHandler;
};

#endif