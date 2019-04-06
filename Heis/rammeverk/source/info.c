#include "info.h"

void info_printStatus(fsm_vars_t elevator){

    printf("\n\n\n#### ELEVATOR INFO ####\n\nState: %s\nCurrent Floor: %d\nLast Direction: %s\n",info_stateToStr(elevator.state),(elevator.currentFloor +1),info_dirToStr(elevator.lastDir));
}

char* info_stateToStr(fsm_state_t state){

    switch (state) {
      case IDLE: return "IDLE";
      case MOVING: return "MOVING";
      case DOOR_OPEN: return "DOOR OPEN";
      case STOPPED: return "STOPPED";
      case INIT: return "INIT";
    }

}

char* info_dirToStr(elev_motor_direction_t dir){

    switch (dir) {
      case DIRN_UP: return "UP";
      case DIRN_DOWN: return "DOWN";
      case DIRN_STOP: return "STOPPED";
    }


}
