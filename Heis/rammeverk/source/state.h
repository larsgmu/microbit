#ifndef STATE_H
#define STATE_H
#include "elev.h"

typedef enum tag_fsm_state {
    IDLE,
    MOVING,
    DOOR_OPEN,
    STOPPED,
    INIT
} fsm_state_t;


typedef struct tag_fsm_vars_t{
fsm_state_t state;
int currentFloor;
elev_motor_direction_t lastDir;
int queSys[N_FLOORS][N_BUTTONS];
}fsm_vars_t;

#endif
