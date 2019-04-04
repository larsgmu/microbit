#ifndef FSM_H
#define FSM_H
#include "elev.h"
#include "que.h"
#include <stdio.h>
#include "timer.h"
typedef enum {
    IDLE, MOVING, ARRIVED, STOPPED, INIT


} fsm_state_t;

//Type for en heis
typedef struct elev{
fsm_state_t state;
int currentFloor;
elev_motor_direction_t dir;
int queSys[N_FLOORS][N_BUTTONS];
}fsm_vars_t;

//PUBLIC
void addOrder(int floor);
void removeOrder(int order);
void elev_start(fsm_vars_t* elevator);
void updateLights(fsm_vars_t elevator);
void buttonCheck(fsm_vars_t* elevator);
void clearFloor(fsm_vars_t* elevator);
void fsmRunMainLoop(fsm_vars_t* elevator);
int checkStopBtn(fsm_vars_t* elevator);
#endif
