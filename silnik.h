#ifndef SILNIK_H
#define SILNIK_H

#include "dron.hh"
#include "Dr3D_gnuplot_api.hh"
#include "sroba.h"
#include "taflawody.h"

// Główna klasa, która odpowiada za prawidłowe wyświetlanie obiektów w gnuplocie oraz za wykrywanie kolizji z dnem/powierzchnią
class Silnik
{
public:
    enum class DronId
    {
        Czerwony = 1,
        Zielony,
        Zolty
    };

    Silnik();

    void obrocDrona(double kat);
    void wykonajRuchDrona(double kat, double odleglosc);
    void resetDoDomyslnegoPolozenia();
    void ustawAktywnegoDrona(DronId id);

private:
    void stworzDrony();

    drawNS::APIGnuPlot3D gnutplotApi;

    std::vector<std::shared_ptr<Obiekt>> przeszkody; //drony & przeszkody

    std::vector<std::shared_ptr<Dron>> drony;
    Dron *aktywnyDron;

    Dron *dron(DronId id);

    Powierzchnia dno;
    TaflaWody taflaWody; // chwilowo użyj tej samej klasy dla powierzchni
};

#endif // SILNIK_H
