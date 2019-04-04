#include "elev.h"
#include "fsm.h"
#include <stdio.h>



int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    fsm_vars_t e = {INIT};
    elev_start(&e);
    fsmRunMainLoop(&e);

    return 0;
}
