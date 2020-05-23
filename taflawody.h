#ifndef TAFLAWODY_H
#define TAFLAWODY_H

#include "obiekt.h"

class TaflaWody : public Obiekt
{
public:
    TaflaWody(drawNS::APIGnuPlot3D *gnuplotAPI, int z, int startX = -5, int endX = 5, int startY = -5, int endY = 5);

    virtual std::vector<std::vector<Point3D> > surface() const;

    double wyznaczZ(double x) const;

private:
    int z;
    int startX = -5;
    int endX = 5;
    int startY = -5;
    int endY = 5;
};

#endif // TAFLAWODY_H
