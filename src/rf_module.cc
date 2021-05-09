/*
rf_send_modeule.cc

Purpose: Handles operations related to the rf subsystem.

Author: Ryan Amaral
*/

#include "rf_module.h"

START_MODULE(rfs) {
  // Connect to the IPC
  OK(ipc_connect(ipc.rfs.name))

  // Create listener for general requests
  OK(ipc_qrecv("*", rf_general, NULL, IPC_QRECV_MSG))

  // initialize sending queues and thread for sending
  send_queues_package = rf::init()

  // Keep refreshing incoming messages
  for (;;) {
    OK(ipc_refresh())
  }
}

CALLBACK(rfs_general) {
  
  if (strncmp(msg, ipc.rfs.cmd.init, msg_len) == 0) {
    modprintf("initializing rfs...\n");
    // extract init params and send to rf_init
    // todo implement param extraction
    queues_package = rf::init(5, 1000);
  }  
  else if (strncmp(msg, ipc.rfs.cmd.load, msg_len) == 0) {
    modprintf("loading queues package from existing file...\n");
    // extract text for file location and send to load_queues
  }  
  else if (strncmp(msg, ipc.rfs.cmd.save, msg_len) == 0) {
    modprintf("saving queues package to file...\n");
    // extract text for file location and send to save queues with queues package
  } 
  else if (strncmp(msg, ipc.rfs.cmd.qmsg, msg_len) == 0) {
    modprintf("queueing text message to be sent...\n");
    // extract text and other data and send off to rf_add_to_queue
  } 
  else if (strncmp(msg, ipc.rfs.cmd.qpic, msg_len) == 0) {
    modprintf("queueing image message to be sent...\n");
    // extract image and other data and send off to rf_add_to_queue
  }
  else if (strncmp(msg, ipc.rfs.cmd.qtel, msg_len) == 0) {
    // extract text and other data and send off to rf_add_to_queue
    // I'd actually prefer if this was just text
  }
  else if (strncmp(msg, ipc.rfs.cmd.start_send, msg_len) == 0) {
    modprintf("enabling send mode...\n");
    // start a thread to run rf_send
  }
  else if (strncmp(msg, ipc.rfs.cmd.stop_send, msg_len) == 0) {
    modprintf("disabling send mode...\n");
    // signal a stop to a running send thread if active
    rf::send_mode = false;
  }
  else {
    modprintf("misc message incoming: %.*s\n", msg_len, msg);
  }

    modprintf("done!\n");
}

STOP_MODULE(rfs) {
  // Disconnect from the IPC
  ipc_disconnect();
  modprintf("disconnecting rf\n");
}

EXPORT_MODULE(rfs);