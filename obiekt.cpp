#include "obiekt.h"
#include "math.h"

Obiekt::Obiekt(drawNS::APIGnuPlot3D *gnuplotAPI)
    : gnuplotAPI(gnuplotAPI)
{
}

void Obiekt::aktualizuj()
{
    usunZGnuPlota();
    id = gnuplotAPI->draw_surface(surface(), kolor);
}

void Obiekt::ustawKolor(const std::string &kolor)
{
    this->kolor = kolor;
    aktualizuj();
}

void Obiekt::usunZGnuPlota()
{
    if (id == -1)
        return;
    gnuplotAPI->erase_shape(id);
    id = -1;
}
