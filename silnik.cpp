#include "silnik.h"

Silnik::Silnik()
    : gnutplotApi(-5,5,-5,5,-5,5,1000),
      dno(-5),
      powierzchnia(4),
      sroba(0,0,0,0.5,0.5)
{
    gnutplotApi.change_ref_time_ms(0);

    dron.ustawKolor("red");
    dron.rysuj(&gnutplotApi);

    dno.ustawKolor("grey");
    dno.rysuj(&gnutplotApi);

    powierzchnia.ustawKolor("blue");
    powierzchnia.rysuj(&gnutplotApi);

    sroba.ustawKolor("green");
    sroba.rysuj(&gnutplotApi);
}

void Silnik::obrocDrona(double kat)
{
    dron.rotacja(kat);
    sroba.rotacja(kat);
    dron.rysuj(&gnutplotApi);
    sroba.rysuj(&gnutplotApi);
}

void Silnik::wykonajRuchDrona(double kat, double odleglosc)
{
    dron.wykonajRuch(kat, odleglosc);
    sroba.wykonajRuch(kat, odleglosc);

    dron.rysuj(&gnutplotApi);
    sroba.rysuj(&gnutplotApi);
}
