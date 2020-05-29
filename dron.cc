#include "dron.hh"
#include "math.h"

Dron::Dron(drawNS::APIGnuPlot3D *gnuplotAPI, int x, int y, int z, float a, float b, float c)
    : Prostopadloscian(gnuplotAPI, x, y, z, a, b, c)
{
    // Wyznaczam bok dla śrób - sróby powinny nie być za duże w stosunku do drona
    double bokSroby = std::min(c, b) / 3;
    double HSroby = 1;
    Wektor w;
    w[0] = HSroby / 2;
    // Dodaj sroby z "tyłu" drona
    auto s1 = std::unique_ptr<Sroba>(new Sroba(gnuplotAPI, wierzcholki[2] + w, bokSroby, HSroby));
    s1->ustawKolor("green");
    // musimy przenieść, żeby uniknąć błędów kompilacji
    obiektyZalezne.push_back(std::move(s1));

    auto s2 = std::unique_ptr<Sroba>(new Sroba(gnuplotAPI, wierzcholki[1] + w, bokSroby, HSroby));
    s2->ustawKolor("green");
    obiektyZalezne.push_back(std::move(s2));
}

