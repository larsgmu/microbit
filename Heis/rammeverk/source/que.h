#ifndef QUE_H
#define QUE_H

#include "fsm.h"
#include "elev.h"


//PUBLIC
int getNextDir();
bool shouldStop(int floor);


//PRIVATE
bool hasOrdersAbove(bool** que);


#endif
