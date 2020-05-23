#include "silnik.h"

Silnik::Silnik()
    : gnutplotApi(-5,5,-5,5,-5,5,1000),
      dno(-5),
      powierzchnia(4),
      sroba(0,0,0,0.5,0.5)
{
    gnutplotApi.change_ref_time_ms(0);

    //dodajDrona();
    gnutplotApi.draw_surface(dno.surface(), "grey");
    gnutplotApi.draw_surface(powierzchnia.surface(), "blue");

    gnutplotApi.draw_surface(sroba.surface(), "green");
}

void Silnik::obrocDrona(double kat)
{
    usunDrona();
    dron.rotacja(kat);
    dodajDrona();
}

void Silnik::wykonajRuchDrona(double kat, double odleglosc)
{
    usunDrona();
    dron.wykonajRuch(kat, odleglosc);
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
