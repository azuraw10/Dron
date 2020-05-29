#include "silnik.h"

static const int LICZBA_KROKOW_DLA_ANIMACJI = 15; // każdy ruch jest dzielony na 15 mniejszych ruchów, tak żeby animacja była płynna
static const int CZAS_TRWANIA_POJEDYNCZEGO_KROKU = 50;  // w ms, więc kazda animacja będzie trwać 0,75s

static const int minX = -10;
static const int maxX = 10;
static const int minY = minX;
static const int maxY = maxX;
static const int minZ = minX;
static const int maxZ = maxX;

Silnik::Silnik()
    : gnutplotApi(minX,maxX,minY,maxY,minZ,maxZ,-1), // ustaw change_ref_time_ms na -1, tak żeby mieć większą kontrolę nad tym kiedy widok jest odświeżany
      dronCzerwony(stworzDrona(DronId::Czerwony)),
      dronZielony(stworzDrona(DronId::Zielony)),
      dronZolty(stworzDrona(DronId::Zolty)),
      dno(&gnutplotApi, minZ + 1, minX, maxX, minY, maxY),
      taflaWody(&gnutplotApi, maxZ - 3, minX, maxX, minY, maxY)
{
    dno.ustawKolor("grey");
    taflaWody.ustawKolor("blue");

    Prostopadloscian *p1 = new Prostopadloscian(&gnutplotApi, 4, 4, -1, 2, 2, 4);
    p1->ustawKolor("black");

    Prostopadloscian *p2 = new Prostopadloscian(&gnutplotApi, -4, -4, -1, 2, 2, 4);
    p2->ustawKolor("black");

    obiekty.push_back(std::shared_ptr<Obiekt>(p1));
    obiekty.push_back(std::shared_ptr<Obiekt>(p2));
    obiekty.push_back(dronZielony);
    obiekty.push_back(dronZolty);
    obiekty.push_back(dronCzerwony);

    aktywnyDron = dronCzerwony.get();

    gnutplotApi.redraw();
}

void Silnik::obrocDrona(double kat)
{
    double katKrok = kat / LICZBA_KROKOW_DLA_ANIMACJI;

    for (int i = 0; i < LICZBA_KROKOW_DLA_ANIMACJI; ++i) {
        aktywnyDron->rotacja(katKrok);
        gnutplotApi.redraw();
        std::this_thread::sleep_for(std::chrono::milliseconds(CZAS_TRWANIA_POJEDYNCZEGO_KROKU));
    }
}

void Silnik::wykonajRuchDrona(double kat, double odleglosc)
{
    double odlKrok = odleglosc / LICZBA_KROKOW_DLA_ANIMACJI;

    double przesuniecieZ = odleglosc * sin(kat * M_PI/180);
    bool czyWDol = przesuniecieZ < -0.000001;

    for (int i = 0; i < LICZBA_KROKOW_DLA_ANIMACJI; ++i) {
        aktywnyDron->wykonajRuch(kat, odlKrok);
        if (czyWDol) {
            // sprawdzamy tylko jeśli poruszamy sie "w dół"
            if (dno.pobierzZ() > aktywnyDron->minZ()) {
                std::cout << "Osiągnięto dno! Ruch drona został przerwany" << endl;
                // teraz musimy zaktualizować wartość Z dla drona, żeby nie był poniżej dna
                aktywnyDron->zmienZDlaDolnejPodstawyOWartosc(dno.pobierzZ() - aktywnyDron->minZ());
                gnutplotApi.redraw();
                break;
            }
        } else {
            double zDlaTaflyWody = taflaWody.wyznaczZ(aktywnyDron->srodekDlaGlownego()[0]);
            // pozwalamy się wyburzyć, tak żeby środek podstawy nie wystawał ponad tafle wody
            if (zDlaTaflyWody < aktywnyDron->zDlaDolnejPodstawy()) {
                aktywnyDron->zmienZDlaDolnejPodstawyOWartosc(zDlaTaflyWody - aktywnyDron->zDlaDolnejPodstawy());
            }
        }

        gnutplotApi.redraw();
        std::this_thread::sleep_for(std::chrono::milliseconds(CZAS_TRWANIA_POJEDYNCZEGO_KROKU));
    }
}

void Silnik::resetDoDomyslnegoPolozenia()
{
//    dron->usunZGnuPlota();
//    dron = stworzDrona();
//    gnutplotApi.redraw();
}

Dron *Silnik::stworzDrona(DronId id)
{
    Dron *dron ;
    switch (id) {
    case DronId::Zolty: {
        dron = new Dron(&gnutplotApi, -2, 2, -5);
        dron->ustawKolor("yellow");
        break;
    }
    case DronId::Czerwony: {
        dron = new Dron(&gnutplotApi);
        dron->ustawKolor("red");
        break;
    }
    case DronId::Zielony: {
        dron = new Dron(&gnutplotApi, 2, 2, 5);
        dron->ustawKolor("green");
        break;
    }
    }

    return dron;
}

std::shared_ptr<Dron> Silnik::dron(Silnik::DronId id)
{
    switch (id) {
        case DronId::Zolty: return dronZolty;
        case DronId::Czerwony: return dronCzerwony;
        case DronId::Zielony: return dronZielony;
    }

    return {};
}
