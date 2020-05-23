#include "taflawody.h"

TaflaWody::TaflaWody(drawNS::APIGnuPlot3D *gnuplotAPI, int z, int startX, int endX, int startY, int endY)
    : Obiekt(gnuplotAPI), z(z), startX(startX), endX(endX), startY(startY), endY(endY)
{

}

std::vector<std::vector<drawNS::Point3D> > TaflaWody::surface() const
{
    std::vector<std::vector<drawNS::Point3D>> wynik;
    for(int x = startX; x <= endX; ++x) {
        std::vector<drawNS::Point3D> linia;
        for (int y = startY; y <= endY; ++y) {
            linia.push_back(drawNS::Point3D(x, y, wyznaczZ(x)));
        }
        wynik.push_back(linia);
    }

    return wynik;
}

double TaflaWody::wyznaczZ(double x) const
{
    return z + cos(x);
}
