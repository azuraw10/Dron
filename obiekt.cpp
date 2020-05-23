#include "obiekt.h"
#include "math.h"

Obiekt::Obiekt()
{
}

void Obiekt::rysuj(drawNS::APIGnuPlot3D *gnuplotAPI)
{
    usunZGnuPlota(gnuplotAPI);
    id = gnuplotAPI->draw_surface(surface(), kolor);
}

void Obiekt::ustawKolor(const std::string &kolor)
{
    this->kolor = kolor;
}

void Obiekt::usunZGnuPlota(drawNS::APIGnuPlot3D *gnuplotAPI)
{
    if (id == -1)
        return;
    gnuplotAPI->erase_shape(id);
}
