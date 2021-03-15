/*
rf_send_modeule.cc

Purpose: Handles perations related to the rf sending subsystem.

Author: Ryan Amaral
*/

#include "rf_send.h"
#include "client_api.h"

int rf_send_server_start(void*);
int rf_send_server_stop(void*);
static void process_general_msg(char* msg, size_t msg_len, void* data);

SubsystemModule rf_send_module = {.start = rf_send_server_start,
                                  .stop = rf_send_server_stop};

int rf_send_server_start(void* data) {
  // Connect to the IPC
  if (ipc_connect(ipc.pay.name) != 0) {
    fprintf(stderr, "[rfs] failed to connect to the IPC\n");
    return 0;
  }

  // Create listener for general requests
  if (ipc_qrecv("*", process_general_msg, NULL, IPC_QRECV_MSG) < 0) {
    fprintf(stderr, "[rfs] ipc_qrecv(\"*\") failed\n");
    return 0;
  }

  // Keep refreshing incoming messages
  for (;;) {
    if (ipc_refresh() < 0) {
      fprintf(stderr, "[rfs] ipc_refresh() failed\n");
      return 0;
    }
  }
}

int rf_send_server_stop(void* data) {
  // Disconnect from the IPC
  ipc_disconnect();
}

static void process_general_msg(char* msg, size_t msg_len, void* data) {
  // Take pic
  if (strncmp(msg, ipc.rfs.cmd.qmsg, msg_len) == 0) {
    printf("[rfs] queueing text message to be sent...\n");

    printf("[rfs] done!\n");
  } 
  else if (strncmp(msg, ipc.rfs.cmd.qpic, msg_len) == 0) {
    printf("[rfs] queueing image message to be sent...\n");

    printf("[rfs] done!\n");
  }
  else if (strncmp(msg, ipc.rfs.cmd.qtel, msg_len) == 0) {
    printf("[rfs] queueing paired data message to be sent...\n");

    printf("[rfs] done!\n");
  }
  else if (strncmp(msg, ipc.rfs.cmd.start_send, msg_len) == 0) {
    printf("[rfs] enabling send mode...\n");

    printf("[rfs] done!\n");
  }
  else if (strncmp(msg, ipc.rfs.cmd.stop_send, msg_len) == 0) {
    printf("[rfs] disabling send mode...\n");

    printf("[rfs] done!\n");
  }
  else {
    printf("[rfs] misc message incoming: %.*s\n", msg_len, msg);
  }
}