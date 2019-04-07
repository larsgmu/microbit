/**
 * @file
 * @brief A module containing all fsm functions
 *
 */

#ifndef FSM_H
#define FSM_H

#include "logic.h"
#include "timer.h"
#include "queue.h"
#include "info.h"

/**
 * @brief Basic initialization, sends the elevator
 * to the nearest floor, and updates its variables.
 *
 * @param[out] elevator Elevator @c struct.
 *
 */
void fsm_startElev(fsm_vars_t* elevator);

/**
 * @brief A simple trigger function checking if the elevator,
 * is currently between two floors.
 *
 * @return 1 if @p elevator is between two floors, 0 if not.
 *
 */
int fsm_betweenFloors();

/**
 * @brief A trigger function checking if the
 * elevator is currently at a floor.
 *
 * @param[in,out] elevator Elevator @c struct.
 *
 * @return 1 if the elevator is at a floor and set
 * the floor indicator light. 0 if not at a floor.
 *
 */
int fsm_atFloor(fsm_vars_t* elevator);

/**
 * @brief Copy a list of integers from one buffer to another,
 * reversing the order of the output in the process.
 *
 * @param[in]  p_from Source buffer.
 * @param[out] p_to   Destination buffer.
 * @param[in]  size Number of integers in the buffer.
 *
 * @return 0 on success, 1 if either @p p_from or @p p_to
 * is a @c NULL pointer.
 */
void fsm_mainLoop(fsm_vars_t* elevator);

/**
 * @brief Copy a list of integers from one buffer to another,
 * reversing the order of the output in the process.
 *
 * @param[in]  p_from Source buffer.
 * @param[out] p_to   Destination buffer.
 * @param[in]  size Number of integers in the buffer.
 *
 * @return 0 on success, 1 if either @p p_from or @p p_to
 * is a @c NULL pointer.
 */
void fsm_stateError(fsm_vars_t* elevator);


#endif
