#ifndef entity_h
#define entity_h

#include "point.h"
#include "shape.h"

struct Circle {
    point pos;
    int size;
    color c; // TODO: ask if this naming is acceptable
};

#endif // entity_h
