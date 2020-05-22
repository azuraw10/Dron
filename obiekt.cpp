#include "obiekt.h"
#include "math.h"

Obiekt::Obiekt()
{

}

void Obiekt::rotacjaZ(std::vector<Wektor> *vec, const drawNS::Point3D &center, double kat) const
{
    for (uint i = 0; i < vec->size(); ++i) {
        double nowyX = ((*vec)[i][0] - center[0]) * cos(kat * M_PI/180) - ((*vec)[i][1] - center[1]) * sin(kat * M_PI/180) + center[0];
        double nowyY = ((*vec)[i][0] - center[0]) * sin(kat * M_PI/180) + ((*vec)[i][1] - center[1]) * cos(kat * M_PI/180) + center[1];
        (*vec)[i][0] = nowyX;
        (*vec)[i][1] = nowyY;
    }
}
