/**
 * @file
 * @brief A simple library for doing operations on memory
 * buffers consisting of integers
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
    STOPPED,
    INIT
} fsm_state_t;

/**
 * @brief Copy a list of integers from one buffer to another,
 * reversing the order of the output in the process.
 */
typedef struct tag_fsm_vars_t{
fsm_state_t state;
int currentFloor;
elev_motor_direction_t lastDir;
int queSys[N_FLOORS][N_BUTTONS];
}fsm_vars_t;

#endif
