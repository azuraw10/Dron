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
        Czerwony,
        Zielony,
        Zolty
    };

    Silnik();

    void obrocDrona(double kat);
    void wykonajRuchDrona(double kat, double odleglosc);
    void resetDoDomyslnegoPolozenia();

private:
    Dron *stworzDrona(DronId id);

    drawNS::APIGnuPlot3D gnutplotApi;

    std::vector<std::shared_ptr<Obiekt>> obiekty;

    std::shared_ptr<Dron> dronCzerwony;
    std::shared_ptr<Dron> dronZielony;
    std::shared_ptr<Dron> dronZolty;

    Dron *aktywnyDron;

    std::shared_ptr<Dron> dron(DronId id);

    Powierzchnia dno;
    TaflaWody taflaWody; // chwilowo użyj tej samej klasy dla powierzchni
};

#endif // SILNIK_H
