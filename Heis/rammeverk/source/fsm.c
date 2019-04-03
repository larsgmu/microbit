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
void elev_print(fsm_vars_t elevator){
    printf("#### ELEVATOR INFO ####\n\nState: %d\nCurrent Floor: %d\nTarget Floor: %d\nMotor Dir: %d\n",elevator.state,elevator.currentFloor,elevator.targetFloor,elevator.dir);


}

void elev_start(fsm_vars_t elevator){

  printf("\n\nInitializing elevator... \n\n");
  elevator.state = MOVING;
  elevator.dir = DIRN_DOWN;
  elevator.targetFloor = -1;
  elevator.currentFloor = -1;
  elev_set_motor_direction(DIRN_DOWN);
  for (int i = 0; i < N_FLOORS; i++){
    for (int j = 0; j< N_BUTTONS; j++){
      elevator.queSys[i][j] = 0;
    }
  }

  while(elev_get_floor_sensor_signal() == -1){}
  elevator.currentFloor = elev_get_floor_sensor_signal();
  elevator.state = IDLE;
  elevator.dir =  DIRN_STOP;
  elev_set_motor_direction(DIRN_STOP);
  updateLights(elevator);

  printf("\nElevator initialized! \n\n");


  elev_print(elevator);


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
    elev_set_button_lamp(0, 0, elevator.queSys[0][0]);
    elev_set_button_lamp(2, 0, elevator.queSys[0][2]);

    for (int floor = 1; floor<N_FLOORS-1; floor++){
        for (int button = 0; button < N_BUTTONS; button++){
             elev_set_button_lamp(button, floor, elevator.queSys[floor][button]);
        }
    }
    elev_set_button_lamp(1, N_FLOORS-1, elevator.queSys[N_FLOORS-1][1]);
    elev_set_button_lamp(2, N_FLOORS-1, elevator.queSys[N_FLOORS-1][2]);

}

void buttonCheck(fsm_vars_t elevator){

    for(int floor=1; floor< N_FLOORS-1; floor++){
        for(int button=0; button < N_BUTTONS; button++){
            if(elev_get_button_signal(button,floor)){
                elevator.queSys[floor][button] = 1;
                elev_set_button_lamp(button,floor,1);
            }
        }
    }

    if(elev_get_button_signal(0,0)){
        elevator.queSys[0][0] = 1;
        elev_set_button_lamp(0,0,1);
    }
    if(elev_get_button_signal(2,0)){
        elevator.queSys[0][2] = 1;
        elev_set_button_lamp(2,0,1);
    }

    if(elev_get_button_signal(1,N_FLOORS-1)){
        elevator.queSys[N_FLOORS-1][1] = 1;
        elev_set_button_lamp(1,N_FLOORS-1,1);
    }
    if(elev_get_button_signal(2,N_FLOORS-1)){
        elevator.queSys[N_FLOORS-1][2] = 1;
        elev_set_button_lamp(2,N_FLOORS-1,1);
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
