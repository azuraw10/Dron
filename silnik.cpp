#include "silnik.h"

Silnik::Silnik()
    : gnutplotApi(-5,5,-5,5,-5,5,1000),
      dno(-5),
      powierzchnia(4),
      sroba(0,0,0,0.5,0.5)
{
    gnutplotApi.change_ref_time_ms(0);

    dodajDrona();
    gnutplotApi.draw_surface(dno.surface(), "grey");
    gnutplotApi.draw_surface(powierzchnia.surface(), "blue");

    srobaId = gnutplotApi.draw_surface(sroba.surface(), "green");
}

void Silnik::obrocDrona(double kat)
{
    usunDrona();
    gnutplotApi.erase_shape(srobaId);
    dron.rotacja(kat);
    sroba.rotacja(kat);
    dodajDrona();
    srobaId = gnutplotApi.draw_surface(sroba.surface(), "green");
}

void Silnik::wykonajRuchDrona(double kat, double odleglosc)
{
    usunDrona();
    gnutplotApi.erase_shape(srobaId);

    dron.wykonajRuch(kat, odleglosc);
    sroba.wykonajRuch(kat, odleglosc);

    dodajDrona();
    srobaId = gnutplotApi.draw_surface(sroba.surface(), "green");
}

void Silnik::usunDrona()
{
    gnutplotApi.erase_shape(dronId);
}

void Silnik::dodajDrona()
{
    dronId = gnutplotApi.draw_surface(dron.surface(), "red");
}
