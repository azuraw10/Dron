#ifndef SILNIK_H
#define SILNIK_H

#include "dron.hh"
#include "dno.h"
#include "Dr3D_gnuplot_api.hh"
#include "sroba.h"

class Silnik
{
public:
    Silnik();

    void obrocDrona(double kat);
    void wykonajRuchDrona(double kat, double odleglosc);

private:
    drawNS::APIGnuPlot3D gnutplotApi;

    Dron dron;
    Dno dno;
    Dno powierzchnia; // chwilowo użyj tej samej klasy dla powierzchni
};

#endif // SILNIK_H
