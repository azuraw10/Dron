#include "obiekt.h"
#include "math.h"

Obiekt::Obiekt()
{
}

void Obiekt::rysuj(drawNS::APIGnuPlot3D *gnuplotAPI)
{
    if (id != -1) {
        gnuplotAPI->erase_shape(id);
    }
    id = gnuplotAPI->draw_surface(surface(), kolor);
}

void Obiekt::ustawKolor(const std::string &kolor)
{
    this->kolor = kolor;
}
