#include "dno.h"


Dno::Dno(int z, int startX, int endX, int startY, int endY)
    : z(z), startX(startX), endX(endX), startY(startY), endY(endY)
{

}

std::vector<std::vector<drawNS::Point3D> > Dno::surface() const
{
    std::vector<std::vector<drawNS::Point3D>> wynik;
    for(int x = startX; x <= endX; ++x) {
        std::vector<drawNS::Point3D> linia;
        for (int y = startY; y <= endY; ++y) {
            linia.push_back(drawNS::Point3D(x, y, z));
        }
        wynik.push_back(linia);
    }

    return wynik;
}
