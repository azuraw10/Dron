#ifndef DRON_HH
#define DRON_HH

#include <iostream>
#include "prostopadl.hh"
#include "Wektor.hh"
#include "bryla.hh"
#include "Macierz.hh"

#include <vector>
#include "Dr3D_gnuplot_api.hh"
#include "obiekt.h"

using drawNS::Point3D;

//clasa dron dziedziczy z prostopad długości boków oraz z bryly orientacje
// metody na wyliczenie orientacji są w bryle, natomiast w tej klasie jest metoda na wyliczanie wierzcholkow po ruchu
class dron : public Obiekt, public prostopad, public bryla
{    
    public:
    //konstruktor w którym wyznaczam zależności współrzędnych każdego punktu w zależności punktu S
    dron(int x=0, int y=0, int z=0, float a=2, float b=2, float c=2);

    //funkcja wyliczająca wektory wierzcholkow
    Wektor licz_wierzcholki(const Wektor S);

    std::vector<std::vector<Point3D> > surface() const override;

private:
    Wektor A,B,C,D,E,F,G,H;//abcd podstawa efgh górna podstawa
    Wektor S;
};

#endif
