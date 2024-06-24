#include "doublerect.h"

doubleRect::doubleRect(double x, double y, double w, double h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

doubleRect::doubleRect() {
    this->x = -1;
    this->y = -1;
    this->w = -1;
    this->h = -1;
}

double doubleRect::getX () {
    return x;
}

double doubleRect::getY () {
    return y;
}

double doubleRect::getW () {
    return w;
}

double doubleRect::getH () {
    return h;
}
