#include "fsm.h"






//Sjekker om det er bestillinger over gjeldende etasje, retunerer bool(som er int i C)
int hasOrdersAbove(fsm_vars_t elevator){
    for (int i = (elevator.currentFloor+1); i<N_FLOORS; i++){
        for (int p = 0; p < N_BUTTONS; p++){
            if (elevator.queSys[i][p])
                return 1;
        }
    }
    return 0;
}

int hasOrdersBelow(fsm_vars_t elevator){
    for(int i = 0; i<elevator.currentFloor; i++){
        for (int p = 0; p < N_BUTTONS; p++){
            if (elevator.queSys[i][p])
                return 1;
        }
    }
    return 0;
}


/*

Bruker shouldISTop her:

if (getFloor != -1){
        shouldIStop();
    }
*/


void elev_start(fsm_vars_t elevator){
  elevator.state = MOVING;
  elevator.dir = DIRN_DOWN;
  elevator.targetFloor = 0;
  elevator.currentFloor = -1;
  elev_set_motor_direction(DIRN_DOWN);

  for (int i = 0; i < N_FLOORS; i++){
    for (int j = 0; j< N_BUTTONS; j++){
      elevator.queSys[i][j] = 0;
    }
  }

  while(elevator.currentFloor != elevator.targetFloor){
    if(elev_get_floor_sensor_signal()!=-1){
      elevator.currentFloor = elev_get_floor_sensor_signal();
    }
  }

  elevator.state=IDLE;
  elevator.dir =  DIRN_STOP;
  elev_set_motor_direction(DIRN_STOP);


}

int shouldIStop(fsm_vars_t elevator){

    switch (elevator.dir) {
        case DIRN_UP:
            return
                elevator.queSys[elevator.currentFloor][1] ||
                elevator.queSys[elevator.currentFloor][2] ||
                !hasOrdersAbove(elevator);
        case DIRN_DOWN:
            return
                elevator.queSys[elevator.currentFloor][0] ||
                elevator.queSys[elevator.currentFloor][2] ||
                !hasOrdersBelow(elevator);
        case DIRN_STOP:
        default:
            return 1;
    }

}

//Oppdatterer lysene for knappene
void updateLights(fsm_vars_t elevator){
    for (int floor = 0; floor<N_FLOORS; floor++){
        for (int button = 0; button < N_BUTTONS; button++){
             elev_set_button_lamp(button, floor, elevator.queSys[floor][button]);
        }
    }
}

void buttonCheck(fsm_vars_t elevator){

    for(int i=0; i< N_FLOORS; i++){
        for(int j=0; j < N_BUTTONS; j++){
            if(elev_get_button_signal(j,i)){
                elevator.queSys[i][j] = 1;
            }
        }
    }
}

void clearFloor(fsm_vars_t elevator){
    elevator.queSys[elevator.currentFloor][0]=0;
    elevator.queSys[elevator.currentFloor][1]=0;
    elevator.queSys[elevator.currentFloor][2]=0;
    updateLights(elevator);
}

void fsmRunMainLoop(fsm_vars_t elevator){

  while(1) {



/*

    if (arrivedAtFloor()){
        swich(elev.state){
            case IDLE:

            case MOVING:

            case ARRIVED:

            case STOPPED:


        }
    }

    //if (doorTimerEnded())


*/
  }
}



//SPØRSMÅL
//typedef enum |navn| {} navn;
