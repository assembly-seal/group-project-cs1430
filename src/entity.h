#ifndef entity_h
#define entity_h

#include "point.h"
#include "color.h"
#include "shape.h"

struct Circle {
    Point pos;
    int size;
    Color c; // TODO: ask if this naming is acceptable
};

#endif // entity_h
