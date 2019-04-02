#include "fsm.h"


typedef enum {
    IDLE, MOVING, ARRIVED, STOPPED


} fsm_state_t;

//Type for en heis
typedef struct elev{
fsm_state_t state;
//int LastFloor;
int targetFloor;
int currentFloor;
elev_motor_direction_t dir;
int queSys[N_FLOORS][N_BUTTONS];
}fsm_vars_t;



//Sjekker om det er bestillinger over gjeldende etasje, retunerer bool(som er int i C)
int hasOrdersAbove(fsm_vars_t elevator){
    for (int i = (elevator.currentFloor+1); i<N_FLOORS; i++){
        for (int p = 0; p < N_BUTTONS; P++) {
            if (elevator.queSys[i][p])
                return 1;
        }
    }
    return 0;
}

int hasOrdersBelow(fsm_vars_t elevator){
    for (int i = 0; i<elevator.currentFloor; i++){
        for (int p = 0; p < N_BUTTONS; P++) {
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


int shouldIStop(fsm_vars_t elevator){

    switch (elevator.dir) {
        case DIRN_UP:
            return
                elevator.queSys[currentFloor][1] ||
                elevator.queSys[currentFloor][2] ||
                !hasOrdersAbove(elevator);
        case DIRN_DOWN:
            return
                elevator.queSys[currentFloor][0] ||
                elevator.queSys[currentFloor][2] ||
                !hasOrdersBelow(elevator);
        case DIRN_STOP:
        default:
            return 1;
    }

}

//Oppdatterer lysene for knappene
void updateLights(fsm_vars_t elevator) {
    for (int i = 0; i<N_FLOORS; i++){
        for (int p = 0; p < N_BUTTONS; P++) {
             elev_set_button_lamp(elevator.queSys[i][p], i, elevator.queSys[i][p]);
        }
    }
}

void buttonCheck(fsm_vars_t elevator){

    for(int i in N_FLOORS){
        for(int j in N_BUTTONS){
            if(elev_get_button_signal(j,i)){
                elevator.queSys[i][j] = 1;
            }
        }
    }
}

void clearFloor(fsm_vars_t elevator){
    elevator.queSys[currentFloor][0],elevator.queSys[currentFloor][1],elevator.queSys[currentFloor][2] = 0;
    updateLights(elevator);
}

void fsmRunMainLoop{

while(1) {



    if (arrivedAtFloor()) {
        swich(elev.state){
            case IDLE:

            case MOVING:

            case ARRIVED:

            case STOPPED:


        }
    }

    if (doorTimerEnded())



}
}


//SPØRSMÅL
//typedef enum |navn| {} navn;
