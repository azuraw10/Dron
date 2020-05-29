#ifndef PROSTOPADLOSCIAN_H
#define PROSTOPADLOSCIAN_H

#include <iostream>
#include "Wektor.hh"

#include <vector>
#include "Dr3D_gnuplot_api.hh"
#include "obiektzmozliwosciaruchuirotacji.h"

using drawNS::Point3D;

class Prostopadloscian : public ObiektZMozliwosciaRuchuIRotacji
{
public:
    //konstruktor w którym wyznaczam zależności współrzędnych każdego punktu w zależności punktu S
    Prostopadloscian(drawNS::APIGnuPlot3D *gnuplotAPI, int x=0, int y=0, int z=0, float a=3, float b=2, float c=2);

    double kierunekXY() const override;

    double zDlaDolnejPodstawy() const;

    Wektor srodek() override;

private:
    std::vector<std::pair<uint, uint>> powierzchnie() const override;
};

#endif // PROSTOPADLOSCIAN_H
