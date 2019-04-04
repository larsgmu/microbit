#include "fsm.h"

//
// int queSys[N_FLOORS][N_BUTTONS];
//
// void setOrder(int floor, int buttonType){
//   queSys[floor][buttonType] = 1;
// }


int temp = 0;

//Sjekker om det er bestillinger over gjeldende etasje, retunerer bool(som er int i C)
int hasOrdersAbove(fsm_vars_t* elevator){
    for (int i = ((elevator->currentFloor)+1); i<N_FLOORS; i++){
        for (int p = 0; p < N_BUTTONS; p++){
            if (elevator->queSys[i][p])
                return 1;
        }
    }
    return 0;
}

int hasOrdersBelow(fsm_vars_t* elevator){
    for(int floor = 0; floor<elevator->currentFloor; floor++){
        for (int buttons = 0; buttons < N_BUTTONS; buttons++){
            if (elevator->queSys[floor][buttons])
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
    printf("\n\n\n#### ELEVATOR INFO ####\n\nState: %d\nCurrent Floor: %d\nMotor Dir: %d\n",elevator.state,elevator.currentFloor,elevator.dir);


}

void elev_start(fsm_vars_t* elevator){
  printf("\n\nInitializing elevator... \n\n");
  elevator->state = INIT;
  elevator->dir = DIRN_DOWN;
  elevator->currentFloor  = -1;
  elev_set_motor_direction(DIRN_DOWN);
  for (int i = 0; i < N_FLOORS; i++){
    for (int j = 0; j< N_BUTTONS; j++){
      elevator->queSys[i][j] = 0;
    }
  }

  while(elev_get_floor_sensor_signal() == -1){}
  elevator->currentFloor  = elev_get_floor_sensor_signal();
  elevator->state = IDLE;
  elevator->dir =  DIRN_STOP;
  elev_set_motor_direction(DIRN_STOP);
  updateLights(*elevator);

  printf("\nElevator initialized! \n\n");


  elev_print(*elevator);


}

int shouldIStop(fsm_vars_t* elevator){

    if(elev_get_stop_signal()){
      return 1;
    }
    switch (elevator->dir) {
        case DIRN_UP:
            return
                elevator->queSys[elevator->currentFloor][0] ||
                elevator->queSys[elevator->currentFloor][2] ||
                !hasOrdersAbove(elevator);
        case DIRN_DOWN:
            return
                elevator->queSys[elevator->currentFloor][1] ||
                elevator->queSys[elevator->currentFloor][2] ||
                !hasOrdersBelow(elevator);
        case DIRN_STOP:
        default:
            return 1;
    }

    return 0;

}

//Oppdatterer lysene for knappene
void updateLights(fsm_vars_t elevator){

  /* Med assert
    elev_set_button_lamp(0, 0, elevator.queSys[0][0]);
    elev_set_button_lamp(2, 0, elevator.queSys[0][2]);
    elev_set_button_lamp(1, N_FLOORS-1, elevator.queSys[N_FLOORS-1][1]);
    elev_set_button_lamp(2, N_FLOORS-1, elevator.queSys[N_FLOORS-1][2]);
*/
//  printf("\n\n Etage: %d\nKnapp: %d\nVerdi: %d",1,2,elevator.queSys[0][0]);
    for (int floor = 0; floor<N_FLOORS; floor++){
        for (int button = 0; button < N_BUTTONS; button++){
             elev_set_button_lamp(button, floor, elevator.queSys[floor][button]);
        }
    }



}

void buttonCheck(fsm_vars_t* elevator){

    for(int floor=0; floor< N_FLOORS; floor++){
        for(int button=0; button < N_BUTTONS; button++){
            if(elev_get_button_signal(button,floor)){
                elevator->queSys[floor][button] = 1;
                temp = 1;
                elev_set_button_lamp(button,floor,1);
            }
        }
    }

/* Med assert
    if(elev_get_button_signal(0,0)){
        elevator.queSys[0][0] = 1;
        elev_set_button_lamp(0,0,1);
    }
    if(elev_get_button_signal(2,0)){
        elevator.queSys[0][2] = 1;
        elev_set_butt(int)elevator.dir;on_lamp(2,0,1);
    }

    if(elev_get_button_signal(1,N_FLOORS-1)){
        elevator.queSys[N_FLOORS-1][1] = 1;
        elev_set_button_lamp(1,N_FLOORS-1,1);
    }
    if(elev_get_button_signal(2,N_FLOORS-1)){
        elevator.queSys[N_FLOORS-1][2] = 1;
        elev_set_button_lamp(2,N_FLOORS-1,1);
    }
    */

}

int arrivedAtFloor(fsm_vars_t* elevator){
  if(elev_get_floor_sensor_signal()!=-1){
    elevator->currentFloor = elev_get_floor_sensor_signal();
    elev_set_floor_indicator(elev_get_floor_sensor_signal());
    return 1;
  }
  return 0;
}

void clearFloor(fsm_vars_t* elevator){
    elevator->queSys[elevator->currentFloor][0]=0;
    elevator->queSys[elevator->currentFloor][1]=0;
    elevator->queSys[elevator->currentFloor][2]=0;
    updateLights(*elevator);
}

elev_motor_direction_t getNextDir(fsm_vars_t* elevator){
  switch (elevator->dir) {
    case DIRN_DOWN:
      if(hasOrdersBelow(elevator)){
        return elevator->dir = DIRN_DOWN;
      }
    case DIRN_UP:
      if (hasOrdersAbove(elevator)){
        return elevator->dir = DIRN_UP;
      }
    case DIRN_STOP:
      if(elev_get_floor_sensor_signal()==-1){
        for(int floor = 0; floor < N_FLOORS; floor++){
          for(int button=0; button<N_BUTTONS; button++){
            if(elev_get_button_signal(button,floor) && elevator->currentFloor<=1 && floor<2){
              return elevator->dir = DIRN_DOWN;
            }
            if((elev_get_button_signal(button,floor)) && floor>=2 && elevator->currentFloor>1){
              return elevator->dir = DIRN_UP;
            }
          }
        }

      }
      if(hasOrdersAbove(elevator)){
        return elevator->dir = DIRN_UP;
      }
      if(hasOrdersBelow(elevator)){
        return elevator->dir = DIRN_DOWN;
      }
    default:
      return elevator->dir = DIRN_STOP;

  }
}

int checkStopBtn(fsm_vars_t* elevator){
    if(elev_get_stop_signal()){
      printf("\n\nSTOP BUTTON PRESSED!\n\n");
      elevator->state = STOPPED;
      elevator->dir = DIRN_STOP;
      return 1;
    }
    return 0;
}

void clearAll(fsm_vars_t* elevator){

  for(int floor = 0; floor < N_FLOORS; floor++){
    for(int button = 0; button < N_BUTTONS; button++){
      elevator->queSys[floor][button] = 0;
    }
  }
  //elevator->currentFloor  = elev_get_floor_sensor_signal();
  temp = 0;
  updateLights(*elevator);

}

int betweenFloors(){
  if(elev_get_floor_sensor_signal() == -1){
    return 1;
  }
  return 0;
}

void fsmRunMainLoop(fsm_vars_t* elevator){
  int timer_started = 0;
  while(1) {

    if (arrivedAtFloor(elevator)){

        switch(elevator->state){
            case IDLE:
              buttonCheck(elevator);
              clearFloor(elevator);
              elevator->dir = getNextDir(elevator);
              if(((int)elevator->dir)!=0){
                elev_set_motor_direction(elevator->dir);
                elevator->state = MOVING;
                elev_print(*elevator);
              }
              checkStopBtn(elevator);
              break;

            case MOVING:
              buttonCheck(elevator);
              if(shouldIStop(elevator)){
                elevator->state = ARRIVED;
                elev_print(*elevator);
                elev_set_motor_direction(DIRN_STOP);
                //elevator->currentFloor  = elev_get_floor_sensor_signal();
              }
              checkStopBtn(elevator);
              break;

            case ARRIVED:
              buttonCheck(elevator);
              clearFloor(elevator);
              if(timer_started==0){
                  start_timer();
                  elev_set_door_open_lamp(1);
                  timer_started=1;
              }
              checkStopBtn(elevator);
              break;

            case STOPPED:
              elev_set_motor_direction(DIRN_STOP);
              clearAll(elevator);
              while(elev_get_stop_signal()){
                elev_set_door_open_lamp(1);
                elev_set_stop_lamp(1);
                timer_started=0;
              }
              elev_set_stop_lamp(0);
              if(timer_started==0){
                start_timer();
                elev_set_door_open_lamp(1);
                timer_started=1;
              }
              break;
            default:
              break;
        }
        buttonCheck(elevator);
    }

    if(betweenFloors()){
      switch(elevator->state){

        case IDLE:
          buttonCheck(elevator);
          elevator->dir = getNextDir(elevator);
          if((int)elevator->dir){
            elev_set_motor_direction(elevator->dir);
            elevator->state = MOVING;
            elev_print(*elevator);
          }
          checkStopBtn(elevator);
          break;

        case MOVING:
          buttonCheck(elevator);
          checkStopBtn(elevator);
          break;

        case STOPPED:
          elev_set_motor_direction(DIRN_STOP);
          elevator->dir = DIRN_STOP;
          clearAll(elevator);
          while(elev_get_stop_signal()){
            elev_set_stop_lamp(1);
          }
          elev_set_stop_lamp(0);
          elevator->state = IDLE;
          elev_print(*elevator);

          break;

        default:
          break;
        }
      }

  if(hodor()){
      switch (elevator->state) {
        case ARRIVED:
          timer_started = 0;
          elevator->state = IDLE;
          elev_set_door_open_lamp(0);
          elev_print(*elevator);
          break;

        case STOPPED:
          timer_started = 0;
          elev_set_door_open_lamp(0);
          elevator->state = IDLE;
          elev_print(*elevator);

          break;
        default:
          break;
      }


    }



  }
}
