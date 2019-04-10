/**
 * @file
 * @brief A simple library for doing logical actions/requests
 * and get functions
 */

#ifndef LOGIC_H
#define LOGIC_H
#include "state.h"
#include <stdio.h>

/**
 * @brief Checks if a button is pressed, if so
 * lights it up.
 *
 * @param[in]  elevator Elevator @c struct.
 *
 */
void logic_updateLights(fsm_vars_t elevator);

/**
 * @brief Checks if stop button is pressed,
 * if so - changes the state of the fsm.
 *
 * @param[out] elevator Elevator @c struct.
 *
 * @return @c 1 if stop button is pressed, @c 0 if not.
 */
int logic_checkStopBtn(fsm_vars_t* elevator);

/**
 * @brief Checks if the elevator should stop at the
 * floor it's currently at/passing, by checking the queue.
 *
 * @param[in] elevator Elevator @c struct.
 *
 * @return 0 if it's not supposed to stop, 1 if the queue in @p elevator
 * has a order on that floor.
 */
int logic_shouldIStop(fsm_vars_t* elevator);

/**
 * @brief Checks if there are orders above the @c currentFloor of
 * @p elevator.
 *
 * @param[in]  elevator Elevator @c struct.
 *
 * @return 1 on if @p elevator has orders above @c currentFloor, 0
 * if not.
 */
int logic_hasOrdersAbove(fsm_vars_t* elevator);

/**
 * @brief Checks if there are orders below the @c currentFloor of
 * @p elevator.
 *
 * @param[in]  elevator Elevator @c struct.
 *
 * @return 1 on if @p elevator has orders below @c currentFloor, 0
 * if not.
 */
int logic_hasOrdersBelow(fsm_vars_t* elevator);

#endif
