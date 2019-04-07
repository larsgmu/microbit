/**
 * @file
 * @brief A simple library for doing operations on memory
 * buffers consisting of integers
 */

#ifndef FSM_H
#define FSM_H

#include "logic.h"
#include "timer.h"
#include "queue.h"
#include "info.h"

void fsm_startElev(fsm_vars_t* elevator);

int fsm_betweenFloors();

int fsm_atFloor(fsm_vars_t* elevator);

void fsm_mainLoop(fsm_vars_t* elevator);

void fsm_stateError(fsm_vars_t* elevator);


#endif
