/**
 * @file
 * @brief A simple library for doing operations on memory
 * buffers consisting of integers
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "state.h"
#include "logic.h"


/**
 * @brief Sets all the parameters to the current floor
 * in the queue to 0, and updates the ligths.
 *
 * @param [in,out] elevator Elevator @c struct
 */
void queue_clearFloor(fsm_vars_t* elevator);

/**
* @brief Sets all the parameters in the queue to 0,
* and updates the ligths
*
* @param [in,out] elevator Elevator @c struct
 */
void queue_clearAll(fsm_vars_t* elevator);

/**
 * @brief Checks what the next direction is based
 * on @c currentFloor and/or @c lastDir
 *
 * @param [in,out] elevator Elevator @c struct
 *
 * @return A @c elev_motor_direction_t based on
 * @c currentFloor and/or @c lastDir. Default DIRN_STOP
 */
elev_motor_direction_t queue_getNextDir(fsm_vars_t* elevator);

/**
* @brief Checks if any buttons are pushed and sets them
* in the queue if true.
*
* @param [out] elevator Elevator @c struct
 */
void queue_checkButtons(fsm_vars_t* elevator);


#endif
