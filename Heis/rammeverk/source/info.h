#ifndef INFO_H
#define INFO_H

#include "state.h"
#include <stdio.h>
#include <string.h>

void info_printStatus(fsm_vars_t elevator);
char* info_stateToStr(fsm_state_t state);
char* info_dirToStr(elev_motor_direction_t dir);

#endif
