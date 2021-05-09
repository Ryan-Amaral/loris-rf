/*
rf_send_modeule.cc

Purpose: Handles operations related to the rf subsystem.

Author: Ryan Amaral
*/

CALLBACK(rfs_general) {
  
  if (strncmp(msg, ipc.rfs.cmd.init, msg_len) == 0) {
    modprintf("initializing rfs...\n");
    // extract init params and send to rf_init
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
    rf::send_mode = false;
  }
  else {
    modprintf("misc message incoming: %.*s\n", msg_len, msg);
  }

    modprintf("done!\n");
}

START_MODULE(rfs) {
  // Connect to the IPC
  OK(ipc_connect(ipc.rfs.name))

  // Create listener for general requests
  OK(ipc_qrecv("*", rf_general, NULL, IPC_QRECV_MSG))

  // initialize thread for sending

  // Keep refreshing incoming messages
  for (;;) {
    OK(ipc_refresh())
  }
}

STOP_MODULE(rfs) {
  // Disconnect from the IPC
  ipc_disconnect();
  modprintf("disconnecting rf\n");
}

EXPORT_MODULE(rfs);