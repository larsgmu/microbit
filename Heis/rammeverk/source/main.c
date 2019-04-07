#include "fsm.h"

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    fsm_vars_t heiSveis = {INIT};
    fsm_startElev(&heiSveis);
    fsm_mainLoop(&heiSveis); //run main loop

    return 0;
}
