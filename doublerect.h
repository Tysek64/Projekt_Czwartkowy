#ifndef DOUBLERECT_H
#define DOUBLERECT_H

class doubleRect
{
private:
    double x;
    double y;
    double w;
    double h;

public:
    doubleRect(double x, double y, double w, double h);
    doubleRect();

    double getX();
    double getY();
    double getW();
    double getH();
};

#endif // DOUBLERECT_H
