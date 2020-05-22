#include "silnik.h"

Silnik::Silnik()
    : gnutplotApi(-5,5,-5,5,-5,5,1000), dno(-5), powierzchnia(4)
{
    gnutplotApi.change_ref_time_ms(0);

    dronId = gnutplotApi.draw_surface(dron.surface(), "red");
    gnutplotApi.draw_surface(dno.surface(), "grey");
    gnutplotApi.draw_surface(powierzchnia.surface(), "blue");
}

void Silnik::obrocDrona(double kat)
{
    usunDrona();
    dron.rotacja(kat);
    dodajDrona();
}

void Silnik::usunDrona()
{
    gnutplotApi.erase_shape(dronId);
}

void Silnik::dodajDrona()
{
    dronId = gnutplotApi.draw_surface(dron.surface(), "red");
}
