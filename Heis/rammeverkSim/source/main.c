#include "fsm.h"

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    //Create a instance of a fsm_vars_t struct(the struct holds all the important variables), and set its initial state to INIT.
    fsm_vars_t heiSveis = {INIT};

    //Run start sequence
    fsm_startElev(&heiSveis);

    //Run main loop
    fsm_mainLoop(&heiSveis);

    return 0;
}
