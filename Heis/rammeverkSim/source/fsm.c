#include "fsm.h"

void fsm_startElev(fsm_vars_t* elevator){
  printf("\n\nInitializing elevator... \n\n");
  elevator->state = INIT;
  elevator->currentFloor  = -1;
  elev_set_motor_direction(DIRN_DOWN);
  //Reset queue
  for (int i = 0; i < N_FLOORS; i++){
    for (int j = 0; j< N_BUTTONS; j++){
      elevator->queue[i][j] = 0;
    }
  }
  //If between floor - hold code until elevator reaches any floor.
  while(elev_get_floor_sensor_signal() == -1){}

  elevator->currentFloor = elev_get_floor_sensor_signal();
  elevator->state = IDLE;
  elevator->lastDir =  DIRN_STOP;
  elev_set_motor_direction(DIRN_STOP);
  logic_updateLights(*elevator);
  printf("\nElevator initialized! \n");
  info_printStatus(*elevator);
}

int fsm_betweenFloors(){
  if(elev_get_floor_sensor_signal() == -1){
    return 1;
  }
  return 0;
}

int fsm_atFloor(fsm_vars_t* elevator){
  //Currfloor is a temporary variable from the floor sensor to prevent setting floorlight in case of buggy sensor.
  int currFloor = elev_get_floor_sensor_signal();
  if(currFloor!=-1){
    elevator->currentFloor = currFloor;
    elev_set_floor_indicator(currFloor);
    if(elevator->state == MOVING){
      info_printStatus(*elevator);
      }
    return 1;
  }
  return 0;
}

void fsm_mainLoop(fsm_vars_t* elevator){
  int timer_started = 0;
  while(1) {
    if (fsm_atFloor(elevator)){

        switch(elevator->state){
            case IDLE:
              //Poll floor and cab buttons.
              queue_checkButtons(elevator);
              queue_clearFloor(elevator);
              //If next direction is not Stop - change state.
              if(((int)queue_getNextDir(elevator))!=0){
                elev_set_motor_direction(queue_getNextDir(elevator));
                elevator->state = MOVING;
                info_printStatus(*elevator);
              }
              //Always poll stop button.
              if(logic_checkStopBtn(elevator)){
                queue_clearAll(elevator);
              }
              break;

            case MOVING:
              queue_checkButtons(elevator);
              if(logic_shouldIStop(elevator)){
                elevator->state = DOOR_OPEN;
                info_printStatus(*elevator);
                elev_set_motor_direction(DIRN_STOP);
              }
              if(logic_checkStopBtn(elevator)){
                queue_clearAll(elevator);
              }
              break;

            case DOOR_OPEN:
              queue_checkButtons(elevator);
              queue_clearFloor(elevator);
              if(timer_started==0){
                  timer_startTimer();
                  elev_set_door_open_lamp(1);
                  timer_started=1;
              }
              if(logic_checkStopBtn(elevator)){
                queue_clearAll(elevator);
              }
              break;

            case STOPPED:
              timer_stopTimer();
              elev_set_motor_direction(DIRN_STOP);
              while(elev_get_stop_signal()){
                queue_clearAll(elevator);
                elev_set_door_open_lamp(1);
                elev_set_stop_lamp(1);
              }

              timer_started=0;
              elev_set_stop_lamp(0);
              elevator->state = DOOR_OPEN;

              break;
            default:
              break;
        }
        //Lets you order while timer is running.
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
          if(logic_checkStopBtn(elevator)){
            queue_clearAll(elevator);
          }
          break;

        case MOVING:
          queue_checkButtons(elevator);
          if(logic_checkStopBtn(elevator)){
            queue_clearAll(elevator);
          }
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

  if(timer_timeIsUp()){
      switch (elevator->state) {
        case DOOR_OPEN:
          timer_started = 0;
          elev_set_door_open_lamp(0);
          elevator->state = IDLE;
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
