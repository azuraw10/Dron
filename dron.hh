#ifndef DRON_HH
#define DRON_HH

#include <iostream>
#include "Wektor.hh"
#include "Macierz.hh"

#include <vector>
#include "Dr3D_gnuplot_api.hh"
#include "obiektzmozliwosciaruchuirotacji.h"
#include "sroba.h"
#include "prostopadloscian.h"

using drawNS::Point3D;

class Dron : public Prostopadloscian
{    
public:
    //konstruktor w którym wyznaczam zależności współrzędnych każdego punktu w zależności punktu S
    Dron(drawNS::APIGnuPlot3D *gnuplotAPI, int x=0, int y=0, int z=0, float a=3, float b=2, float c=2);

    PunktXY srodek() const override;

    double promien() const override;

    void aktualizuj() override;

};

#endif
