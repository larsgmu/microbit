/**
 * @file
 * @brief Module containing enum for the different states
 * and the struct with the variables used by the state machine
 */

#ifndef STATE_H
#define STATE_H
#include "elev.h"

/**
 * @brief Enum containing all states.
 */
typedef enum tag_fsm_state {
    IDLE,
    MOVING,
    DOOR_OPEN,
    EMERGENCY_STOP,
    INIT
} fsm_state_t;

/**
 * @brief Struct containing @c state @c currentFloor @c lastDir
 * and @c queue which are all used for storing the variables during runtime,
 * and hold crictical information like the queue, wich is a @c N_FLOORS @c * @c N_BUTTONS matrix.
 */
typedef struct tag_fsm_vars_t{
fsm_state_t state;
int currentFloor;
elev_motor_direction_t lastDir;
elev_motor_direction_t currDir;
int queue[N_FLOORS][N_BUTTONS];
}fsm_vars_t;

#endif
