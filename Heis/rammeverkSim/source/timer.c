#include "timer.h"

//Global time variable
static time_t start_time;
static int timer_is_active = 0;


void timer_startTimer() {
  start_time = time(NULL);
  timer_is_active = 1;
}

int timer_timeIsUp() {
  if(!timer_is_active){
    return 0;
  }

  time_t current_time = time(NULL);
  //Compare current_time with start_time, if the difference is more or equeal to 3 seconds - time is up.
  if ((difftime(current_time, start_time) >= 3) && timer_is_active){
    timer_is_active = 0;
    return 1;
  }
  return 0;
}

void timer_stopTimer(){

  timer_is_active = 0;

}
