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
void fsm_startElev(fsm_vars_t* elevator);

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
int fsm_betweenFloors();

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
