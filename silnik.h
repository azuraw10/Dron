#ifndef SILNIK_H
#define SILNIK_H

#include "dron.hh"
#include "dno.h"
#include "Dr3D_gnuplot_api.hh"

class Silnik
{
public:
    Silnik();

    void obrocDrona(double kat);

private:
    void usunDrona();
    void dodajDrona();

    drawNS::APIGnuPlot3D gnutplotApi;

    Dron dron;
    uint dronId;
    Dno dno;
    Dno powierzchnia; // chwilowo użyj tej samej klasy dla powierzchni
};

#endif // SILNIK_H
