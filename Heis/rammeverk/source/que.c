#include "que.h"

void printQue(fsm_vars_t elevator){
    printf("\n\n Current Queue:\n\n");
    for(int floor = N_FLOORS; floor > 0; floor--){
      for(int button = N_BUTTONS; button > 0; button--){
        printf(" %d ", elevator.queSys[floor][button]);
      }
      printf("\n");
    }
}
