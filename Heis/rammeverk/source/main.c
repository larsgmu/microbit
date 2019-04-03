#include "elev.h"
#include "fsm.h"
#include <stdio.h>


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    fsm_vars_t e = {
      MOVING
    };
    elev_start(e);



    while (1){
        // Change direction when we reach top/bottom floor
        /*if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }*/

        //printf("STATE: %d\n", (int)e.state);

        e.state = MOVING;
        buttonCheck(e);
        

    // Stop elevator and exit program if the stop button is pressed
    if (elev_get_stop_signal()) {
        elev_set_motor_direction(DIRN_STOP);
        break;

    }

    //fsmRunMainLoop();
}
    return 0;
}
