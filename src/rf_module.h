/*
rf_send_modeule.h

Purpose: Handles perations related to the rf sending subsystem.

Author: Ryan Amaral
*/

#ifndef CUBESAT_CORE_INCLUDE_SUBSYSTEM_SERVER_RF
#define CUBESAT_CORE_INCLUDE_SUBSYSTEM_SERVER_RF

// macros
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE
#endif

// project headers
#include "subsystem_module.h"

#include "rf_module.h"
#include "rf_send.h"
#include "client_api.h"

// standard c libs
#include <signal.h>
#include <string.h>
#include <pthread.h>
#include <queue>

NEW_DOCK_MODULE(rf);

static pthread_t rf_send_thread;

#endif