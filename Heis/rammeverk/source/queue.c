#include "queue.h"


void queue_clearFloor(fsm_vars_t* elevator){
    elevator->queSys[elevator->currentFloor][0]=0;
    elevator->queSys[elevator->currentFloor][1]=0;
    elevator->queSys[elevator->currentFloor][2]=0;
    logic_updateLights(*elevator);
}

void queue_clearAll(fsm_vars_t* elevator){

  for(int floor = 0; floor < N_FLOORS; floor++){
    for(int button = 0; button < N_BUTTONS; button++){
      elevator->queSys[floor][button] = 0;
    }
  }
  //elevator->currentFloor  = elev_get_floor_sensor_signal();
  logic_updateLights(*elevator);

}

elev_motor_direction_t queue_getNextDir(fsm_vars_t* elevator){
  switch (elevator->lastDir) {
    case DIRN_DOWN:
      if(logic_hasOrdersBelow(elevator)){
        return elevator->lastDir = DIRN_DOWN;
      }

    case DIRN_UP:
      if (logic_hasOrdersAbove(elevator)){
        return elevator->lastDir = DIRN_UP;
      }

    case DIRN_STOP:
      if(elev_get_floor_sensor_signal()==-1){
        for(int floor = 0; floor < N_FLOORS; floor++){
          for(int button=0; button<N_BUTTONS; button++){
            if(elev_get_button_signal(button,floor) && elevator->currentFloor>floor){
              return DIRN_DOWN;
            }
            if(elev_get_button_signal(button,floor) && elevator->currentFloor<floor){
              return DIRN_UP;
            }
            if(elev_get_button_signal(button,floor) && elevator->currentFloor==floor && elevator->lastDir == DIRN_DOWN){
              return DIRN_UP;
            }
            if(elev_get_button_signal(button,floor) && elevator->currentFloor==floor && elevator->lastDir == DIRN_UP){
              return DIRN_DOWN;
            }
          }
        }

      }
      if(logic_hasOrdersAbove(elevator)){
        return elevator->lastDir = DIRN_UP;
      }
      if(logic_hasOrdersBelow(elevator)){
        return elevator->lastDir = DIRN_DOWN;
      }
    default:
      return DIRN_STOP;

  }
}

void queue_checkButtons(fsm_vars_t* elevator){

    for(int floor=0; floor< N_FLOORS; floor++){
        for(int button=0; button < N_BUTTONS; button++){
            if(elev_get_button_signal(button,floor)){
                elevator->queSys[floor][button] = 1;
                elev_set_button_lamp(button,floor,1);
            }
        }
    }
}
