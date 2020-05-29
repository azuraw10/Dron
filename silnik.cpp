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
      dno(&gnutplotApi, minZ + 1, minX, maxX, minY, maxY),
      taflaWody(&gnutplotApi, maxZ - 3, minX, maxX, minY, maxY)
{
    stworzDrony();

    dno.ustawKolor("grey");
    taflaWody.ustawKolor("blue");

    Prostopadloscian *p1 = new Prostopadloscian(&gnutplotApi, 4, 4, -1, 2, 2, 4);
    p1->ustawKolor("black");

    Prostopadloscian *p2 = new Prostopadloscian(&gnutplotApi, -4, -4, -1, 2, 2, 4);
    p2->ustawKolor("black");

    przeszkody.push_back(std::shared_ptr<Obiekt>(p1));
    przeszkody.push_back(std::shared_ptr<Obiekt>(p2));

    ustawAktywnegoDrona(DronId::Czerwony);

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
    for (auto d : drony) {
        d->usunZGnuPlota();
    }

    stworzDrony();

    gnutplotApi.redraw();
}

void Silnik::ustawAktywnegoDrona(Silnik::DronId id)
{
    aktywnyDron = dron(id);
}

void Silnik::stworzDrony()
{
    drony.clear();

    auto dronCzerwony = std::shared_ptr<Dron>(new Dron(&gnutplotApi));
    dronCzerwony->ustawKolor("red");

    auto dronZielony = std::shared_ptr<Dron>(new Dron(&gnutplotApi, 2, 2, 5));
    dronZielony->ustawKolor("green");

    auto dronZolty = std::shared_ptr<Dron>(new Dron(&gnutplotApi, -2, 2, -5));
    dronZolty->ustawKolor("yellow");

    drony.push_back(dronCzerwony);
    drony.push_back(dronZielony);
    drony.push_back(dronZolty);
}

Dron *Silnik::dron(Silnik::DronId id)
{
    return drony.at(static_cast<int>(id) - 1).get();
}
