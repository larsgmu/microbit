#include "logic.h"


//Oppdatterer lysene for knappene
void logic_updateLights(fsm_vars_t elevator){
    for (int floor = 0; floor<N_FLOORS; floor++){
        for (int button = 0; button < N_BUTTONS; button++){
             elev_set_button_lamp(button, floor, elevator.queSys[floor][button]);
        }
    }
}

int logic_checkStopBtn(fsm_vars_t* elevator){
    if(elev_get_stop_signal()){
      printf("\n##############################\n#    STOP BUTTON PRESSED!    #\n##############################\n\n");
      elevator->state = STOPPED;
      return 1;
    }
    return 0;
}

int logic_shouldIStop(fsm_vars_t* elevator){
    if(elev_get_stop_signal()){
      return 1;
    }
    switch (elevator->lastDir) {
        case DIRN_UP:
            return
                elevator->queSys[elevator->currentFloor][0] ||
                elevator->queSys[elevator->currentFloor][2] ||
                !logic_hasOrdersAbove(elevator);
        case DIRN_DOWN:
            return
                elevator->queSys[elevator->currentFloor][1] ||
                elevator->queSys[elevator->currentFloor][2] ||
                !logic_hasOrdersBelow(elevator);
        case DIRN_STOP:
        default:
            return 1;
    }
    return 0;
}

int logic_hasOrdersAbove(fsm_vars_t* elevator){
    for (int i = ((elevator->currentFloor)+1); i<N_FLOORS; i++){
        for (int p = 0; p < N_BUTTONS; p++){
            if (elevator->queSys[i][p])
                return 1;
        }
    }
    return 0;
}

int logic_hasOrdersBelow(fsm_vars_t* elevator){
    for(int floor = 0; floor<elevator->currentFloor; floor++){
        for (int buttons = 0; buttons < N_BUTTONS; buttons++){
            if (elevator->queSys[floor][buttons])
                return 1;
        }
    }
    return 0;
}