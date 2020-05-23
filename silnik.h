#ifndef SILNIK_H
#define SILNIK_H

#include "dron.hh"
#include "dno.h"
#include "Dr3D_gnuplot_api.hh"
#include "sroba.h"

// Główna klasa, która odpowiada za prawidłowe wyświetlanie obiektów w gnuplocie
class Silnik
{
public:
    Silnik();

    void obrocDrona(double kat);
    void wykonajRuchDrona(double kat, double odleglosc);
    void resetDoDomyslnegoPolozenia();

private:
    Dron stworzDrona();

    drawNS::APIGnuPlot3D gnutplotApi;

    Dron dron;
    Dno dno;
    Dno powierzchnia; // chwilowo użyj tej samej klasy dla powierzchni
};

#endif // SILNIK_H
