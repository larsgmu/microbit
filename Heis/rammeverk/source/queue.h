#ifndef QUEUE_H
#define QUEUE_H

#include "state.h"
#include "logic.h"



void queue_clearFloor(fsm_vars_t* elevator);

void queue_clearAll(fsm_vars_t* elevator);

elev_motor_direction_t queue_getNextDir(fsm_vars_t* elevator);

void queue_checkButtons(fsm_vars_t* elevator);


#endif
