#ifndef DNO_H
#define DNO_H

#include "obiekt.h"

class Dno : public Obiekt
{
public:
    Dno(drawNS::APIGnuPlot3D *gnuplotAPI, int z, int startX = -5, int endX = 5, int startY = -5, int endY = 5);

    virtual std::vector<std::vector<Point3D> > surface() const;

private:
    int z;
    int startX = -5;
    int endX = 5;
    int startY = -5;
    int endY = 5;
};

#endif // DNO_H
