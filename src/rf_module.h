/*
rf_send_modeule.h

Purpose: Handles perations related to the rf sending subsystem.

Author: Ryan Amaral
*/

#ifndef CUBESAT_CORE_INCLUDE_SUBSYSTEM_SERVER_RF
#define CUBESAT_CORE_INCLUDE_SUBSYSTEM_SERVER_RF

#define _XOPEN_SOURCE

#include "ipc_std.h"
#include "subsystem_module.h"

#include <signal.h>
#include <string.h>
#include <pthread.h>

extern SubsystemModule rf_module;

static pthread_t rf_send_thread;

#endif