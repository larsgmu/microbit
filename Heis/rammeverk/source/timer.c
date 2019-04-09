#include "timer.h"


static time_t start_time;
static int timer_is_active = 0;

void timer_startTimer() {
  start_time = time(NULL);
  timer_is_active = 1;
}

int timer_timeIsUp() {
  time_t current_time = time(NULL);
  if ((difftime(current_time, start_time) >= 3) && timer_is_active){
    timer_is_active = 0;
    return 1;
  }
  return 0;
}
