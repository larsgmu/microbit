#ifndef QUE_H
#define QUE_H

#include "fsm.h"
#include "elev.h"


//PUBLIC
int getNextDir();
int shouldStop(int floor);


//PRIVATE
int hasOrdersAbove(int** que);


#endif
