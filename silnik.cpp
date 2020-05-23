#include "silnik.h"

Silnik::Silnik()
    : gnutplotApi(-5,5,-5,5,-5,5,1000),
      dron(stworzDrona()),
      dno(-5),
      powierzchnia(4)
{
    gnutplotApi.change_ref_time_ms(0);

    dron.rysuj(&gnutplotApi);

    dno.ustawKolor("grey");
    dno.rysuj(&gnutplotApi);

    powierzchnia.ustawKolor("blue");
    powierzchnia.rysuj(&gnutplotApi);
}

void Silnik::obrocDrona(double kat)
{
    dron.rotacja(kat);
    dron.rysuj(&gnutplotApi);;
}

void Silnik::wykonajRuchDrona(double kat, double odleglosc)
{
    dron.wykonajRuch(kat, odleglosc);
    dron.rysuj(&gnutplotApi);
}

void Silnik::resetDoDomyslnegoPolozenia()
{
    dron.usunZGnuPlota(&gnutplotApi);
    dron = stworzDrona();
    dron.rysuj(&gnutplotApi);
}

Dron Silnik::stworzDrona()
{
    Dron dron;
    dron.ustawKolor("red");
    return dron;
}
