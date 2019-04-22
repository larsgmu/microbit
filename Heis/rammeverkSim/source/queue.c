#include "queue.h"


void queue_clearFloor(fsm_vars_t* elevator){
    // Zero floor button lamps on current floor
    elevator->queue[elevator->currentFloor][0]=0;
    elevator->queue[elevator->currentFloor][1]=0;
    elevator->queue[elevator->currentFloor][2]=0;

    logic_updateLights(*elevator);
}

void queue_clearAll(fsm_vars_t* elevator){

  // Zero all floor button lamps
  for(int floor = 0; floor < N_FLOORS; floor++){
    for(int button = 0; button < N_BUTTONS; button++){
      elevator->queue[floor][button] = 0;
    }
  }

  logic_updateLights(*elevator);
}

elev_motor_direction_t queue_getNextDir(fsm_vars_t* elevator){
  switch (elevator->lastDir) {
    case DIRN_DOWN:
      //if it is orders below - continue down.
      if(logic_hasOrdersBelow(elevator)){
        elevator->currDir = DIRN_DOWN;
        return elevator->lastDir = DIRN_DOWN;
      }

    case DIRN_UP:
      //if it is orders above - continue up.
      if (logic_hasOrdersAbove(elevator)){
        elevator->currDir = DIRN_UP;
        return elevator->lastDir = DIRN_UP;
      }

    case DIRN_STOP:
      //If between floors
      if(elev_get_floor_sensor_signal()==-1){
        for(int floor = 0; floor < N_FLOORS; floor++){
          for(int button=0; button<N_BUTTONS; button++){
            //if button called on a floor below the current floor - go down.
            if(elev_get_button_signal(button,floor) && elevator->currentFloor>floor){
              elevator->currDir = DIRN_DOWN;
              return DIRN_DOWN;
            }
            //if button called on a floor above the current floor - go up.
            if(elev_get_button_signal(button,floor) && elevator->currentFloor<floor){
              elevator->currDir = DIRN_UP;
              return DIRN_UP;
            }

            //if button called on the current floor and the last direction was down(implies that the elevator is below currentFloor) - go up.
            if(elev_get_button_signal(button,floor) && elevator->currentFloor==floor && elevator->lastDir == DIRN_DOWN){
              elevator->currDir = DIRN_UP;
              return DIRN_UP;
            }
            //if button called on the current floor and the last direction was up(implies that the elevator is above currentFloor) - go down.
            if(elev_get_button_signal(button,floor) && elevator->currentFloor==floor && elevator->lastDir == DIRN_UP){
              elevator->currDir = DIRN_DOWN;
              return DIRN_DOWN;
            }
          }
        }
      }
      //If at a floor and has orders above - go up.
      if(logic_hasOrdersAbove(elevator)){
        elevator->currDir = DIRN_UP;
        return elevator->lastDir = DIRN_UP;
      }
      //If at a floor and has orders below - go down.
      if(logic_hasOrdersBelow(elevator)){
        elevator->currDir = DIRN_DOWN;
        return elevator->lastDir = DIRN_DOWN;
      }
    default:
      return DIRN_STOP;

  }
}

//Iterate through all buttons, if pressed - add the floor/button to queue and light lamp.
void queue_checkButtons(fsm_vars_t* elevator){
    for(int floor=0; floor< N_FLOORS; floor++){
        for(int button=0; button < N_BUTTONS; button++){
            if(elev_get_button_signal(button,floor)){
                elevator->queue[floor][button] = 1;
                elev_set_button_lamp(button,floor,1);
            }
        }
    }
}
