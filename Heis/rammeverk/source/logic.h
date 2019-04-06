#ifndef LOGIC_H
#define LOGIC_H
#include "state.h"
#include <stdio.h>



void logic_updateLights(fsm_vars_t elevator);
int logic_checkStopBtn(fsm_vars_t* elevator);
int logic_shouldIStop(fsm_vars_t* elevator);
int logic_hasOrdersAbove(fsm_vars_t* elevator);
int logic_hasOrdersBelow(fsm_vars_t* elevator);
#endif
