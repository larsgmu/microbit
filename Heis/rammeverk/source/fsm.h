#ifndef FSM_H
#define FSM_H
#include "elev.h"
#include <stdio.h>

typedef enum {
    IDLE, MOVING, ARRIVED, STOPPED


} fsm_state_t;

//Type for en heis
typedef struct elev{
fsm_state_t state;
//int LastFloor;
int targetFloor;
int currentFloor;
elev_motor_direction_t dir;
int queSys[N_FLOORS][N_BUTTONS];
}fsm_vars_t;

//PUBLIC
void addOrder(int floor);
void removeOrder(int order);
void elev_start(fsm_vars_t elevator);
void updateLights(fsm_vars_t elevator);
void buttonCheck(fsm_vars_t elevator);
void clearFloor(fsm_vars_t elevator);
#endif
