/**
 * @file
 * @brief A simple library for time functions.
 */

#ifndef TIMER_H
#define TIMER_H

#include <time.h>

/**
 * @brief Sets the global variable @c start_time to @c time(NULL),
 * in other words - resetting the timer.
 */
void timer_startTimer();

/**
 * @brief Creates a local timer and compares it to the
 * timer started by @c timer_startTimer()
 *
 * @return 1 if its gone by 3 seconds, and 0 if not.
 */
int timer_timeIsUp();

/**
 * @brief Sets the global variable
 * timer_is_active to 0.
 */
void timer_resetTimer();

#endif
