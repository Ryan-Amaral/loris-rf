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
    // todo extract file name
    queues_package = rf::load_queues("tmp.txt");
  }  
  else if (strncmp(msg, ipc.rfs.cmd.save, msg_len) == 0) {
    modprintf("saving queues package to file...\n");
    // extract text for file location and send to save queues with queues package
    // todo, extract file name
    rf::save_queues(queues_package, "tmp.txt");
  } 
  else if (strncmp(msg, ipc.rfs.cmd.qmsg, msg_len) == 0) {
    modprintf("queueing text message to be sent...\n");
    // extract text and other data and send off to rf_add_to_queue
    // todo: extract message and priority
    rf::add_to_queue(false, "replace me", 0, queues_package);
  } 
  else if (strncmp(msg, ipc.rfs.cmd.qpic, msg_len) == 0) {
    modprintf("queueing image message to be sent...\n");
    // extract image and other data and send off to rf_add_to_queue
    // todo: extract image file and priority
    rf::add_to_queue(true, "file.jpg", 0, queues_package);
  }
  else if (strncmp(msg, ipc.rfs.cmd.qtel, msg_len) == 0) {
    // extract text and other data and send off to rf_add_to_queue
    // I'd actually prefer if this was just text
  }
  else if (strncmp(msg, ipc.rfs.cmd.start_send, msg_len) == 0) {
    modprintf("enabling send mode...\n");
    // start a thread to run rf_send
    rf::send((void*)queues_package);
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
  // make sure to stop sending just in case
  rf::send_mode = false;
}

EXPORT_MODULE(rfs);