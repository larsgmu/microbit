#include "fsm.h"

void fsm_startElev(fsm_vars_t* elevator){
  printf("\n\nInitializing elevator... \n\n");
  elevator->state = INIT;
  elevator->lastDir = DIRN_DOWN;
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
  elevator->lastDir =  DIRN_STOP;
  elev_set_motor_direction(DIRN_STOP);
  logic_updateLights(*elevator);
  printf("\nElevator initialized! \n");
  info_printStatus(*elevator);
}


void fsm_stateError(fsm_vars_t* elevator){
  if(elevator->currentFloor==-1){
    printf("\n\n*SENSOR ERROR - RESTARTING*\n\n");
    fsm_startElev(elevator);
  }
}


int fsm_betweenFloors(){
  if(elev_get_floor_sensor_signal() == -1){
    return 1;
  }
  return 0;
}

int fsm_atFloor(fsm_vars_t* elevator){
  if(elev_get_floor_sensor_signal()!=-1){
    elevator->currentFloor = elev_get_floor_sensor_signal();
    elev_set_floor_indicator(elev_get_floor_sensor_signal());
    if(elevator->state == MOVING)info_printStatus(*elevator);
    return 1;
  }
  return 0;
}

void fsm_mainLoop(fsm_vars_t* elevator){
  int timer_started = 0;
  while(1) {
    fsm_stateError(elevator);
    if (fsm_atFloor(elevator)){

        switch(elevator->state){
            case IDLE:
              queue_checkButtons(elevator);
              queue_clearFloor(elevator);

              if(((int)queue_getNextDir(elevator))!=0){
                elev_set_motor_direction(queue_getNextDir(elevator));
                elevator->state = MOVING;
                info_printStatus(*elevator);
              }
              if(logic_checkStopBtn(elevator))queue_clearAll(elevator);
              break;

            case MOVING:
              queue_checkButtons(elevator);
              if(logic_shouldIStop(elevator)){
                elevator->state = DOOR_OPEN;
                info_printStatus(*elevator);
                elev_set_motor_direction(DIRN_STOP);
                //elevator->currentFloor  = elev_get_floor_sensor_signal();
              }
              if(logic_checkStopBtn(elevator))queue_clearAll(elevator);
              break;

            case DOOR_OPEN:
              queue_checkButtons(elevator);
              queue_clearFloor(elevator);
              if(timer_started==0){
                  timer_startTimer();
                  elev_set_door_open_lamp(1);
                  timer_started=1;
              }
              if(logic_checkStopBtn(elevator))queue_clearAll(elevator);
              break;

            case STOPPED:
              elev_set_motor_direction(DIRN_STOP);
              while(elev_get_stop_signal()){
                queue_clearAll(elevator);
                elev_set_door_open_lamp(1);
                elev_set_stop_lamp(1);
                timer_started=0;
              }
              elev_set_stop_lamp(0);
              elevator->state = DOOR_OPEN;
              break;
            default:
              break;
        }
        queue_checkButtons(elevator);
    }

    if(fsm_betweenFloors()){
      switch(elevator->state){

        case IDLE:
          queue_checkButtons(elevator);
          if((int)queue_getNextDir(elevator)){
            elev_set_motor_direction(queue_getNextDir(elevator));
            elevator->state = MOVING;
            info_printStatus(*elevator);
          }
          if(logic_checkStopBtn(elevator))queue_clearAll(elevator);
          break;

        case MOVING:
          queue_checkButtons(elevator);
          if(logic_checkStopBtn(elevator))queue_clearAll(elevator);
          break;

        case STOPPED:
          elev_set_motor_direction(DIRN_STOP);
          queue_clearAll(elevator);
          while(elev_get_stop_signal()){
            elev_set_stop_lamp(1);
          }
          elev_set_stop_lamp(0);
          elevator->state = IDLE;
          info_printStatus(*elevator);

          break;

        default:
          break;
        }
      }

  if(timer_hodor()){
      switch (elevator->state) {
        case DOOR_OPEN:
          timer_started = 0;
          elevator->state = IDLE;
          elev_set_door_open_lamp(0);
          info_printStatus(*elevator);
          break;

        case STOPPED:
          timer_started = 0;
          elev_set_door_open_lamp(0);
          elevator->state = IDLE;
          info_printStatus(*elevator);

          break;
        default:
          break;
      }
    }


  }
}
