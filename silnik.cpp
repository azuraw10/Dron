#include "silnik.h"

static int LICZBA_KROKOW_DLA_ANIMACJI = 15; // każdy ruch jest dzielony na 15 mniejszych ruchów, tak żeby animacja była płynna
static int CZAS_TRWANIA_POJEDYNCZEGO_KROKU = 50;  // w ms, więc kazda animacja będzie trwać 0,75s

Silnik::Silnik()
    : gnutplotApi(-5,5,-5,5,-5,5,1000),
      dron(stworzDrona()),
      dno(&gnutplotApi, -4),
      powierzchnia(&gnutplotApi, 4)
{
    gnutplotApi.change_ref_time_ms(-1); // ustaw na -1, tak żeby mieć większą kontrolę nad tym kiedy widok jest odświeżany

    dno.ustawKolor("grey");
    powierzchnia.ustawKolor("blue");

    gnutplotApi.redraw();
}

void Silnik::obrocDrona(double kat)
{
    double katKrok = kat / LICZBA_KROKOW_DLA_ANIMACJI;

    for (int i = 0; i < LICZBA_KROKOW_DLA_ANIMACJI; ++i) {
        dron.rotacja(katKrok);
        gnutplotApi.redraw();
        std::this_thread::sleep_for(std::chrono::milliseconds(CZAS_TRWANIA_POJEDYNCZEGO_KROKU));
    }
}

void Silnik::wykonajRuchDrona(double kat, double odleglosc)
{
    double odlKrok = odleglosc / LICZBA_KROKOW_DLA_ANIMACJI;

    for (int i = 0; i < LICZBA_KROKOW_DLA_ANIMACJI; ++i) {
        dron.wykonajRuch(kat, odlKrok);
        if (dno.getZ() > dron.zDlaDolnejPodstawy()) {
            std::cout << "OSiągnięto dno! Ruch dron został przerwany" << endl;
            // teraz musimy zaktualizować wartość Z dla drona, żeby nie był poniżej dna
            dron.zninZDlaDolnejPodstawyOWartosc(dno.getZ() - dron.zDlaDolnejPodstawy());
            gnutplotApi.redraw();
            break;
        }
        gnutplotApi.redraw();
        std::this_thread::sleep_for(std::chrono::milliseconds(CZAS_TRWANIA_POJEDYNCZEGO_KROKU));
    }
}

void Silnik::resetDoDomyslnegoPolozenia()
{
    dron.usunZGnuPlota();
    dron = stworzDrona();
    gnutplotApi.redraw();
}

Dron Silnik::stworzDrona()
{
    Dron dron(&gnutplotApi);
    dron.ustawKolor("red");
    return dron;
}
