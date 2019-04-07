/**
 * @file
 * @brief A simple library for printing to console
 */

#ifndef INFO_H
#define INFO_H

#include "state.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Prints info about the @p elevator to console,
 *
 * @param[in] elevator Elevator @c struct.
 *
 */
void info_printStatus(fsm_vars_t elevator);

/**
 * @brief Turns a @c state into a string (@c char @c * in @c C)
 *
 * @param[in]  elevator Elevator @c struct.
 *
 * @return A @c char @c * containing the current state
 * of @p elevator.
 */
char* info_stateToStr(fsm_state_t state);

/**
 * @brief Turns a @c direction into a string (@c char @c * in @c C)
 *
 * @param[in]  elevator Elevator @c struct.
 *
 * @return A @c char @c * containing the current/last direction
 * of @p elevator.
 */
char* info_dirToStr(elev_motor_direction_t dir);

#endif
