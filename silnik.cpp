#include "silnik.h"

static const int LICZBA_KROKOW_DLA_ANIMACJI_OBROT = 15; // każdy ruch jest dzielony na 15 mniejszych ruchów, tak żeby animacja była płynna
static const int CZAS_TRWANIA_POJEDYNCZEGO_KROKU_OBROT = 50;  // w ms, więc kazda animacja będzie trwać 0,75s

static const int CZAS_TRWANIA_POJEDYNCZEGO_KROKU_RUCH = 20;

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

    przeszkody.push_back(std::shared_ptr<Prostopadloscian>(p1));
    przeszkody.push_back(std::shared_ptr<Prostopadloscian>(p2));

    gnutplotApi.redraw();
}

void Silnik::obrocDrona(double kat)
{
    double katKrok = kat / LICZBA_KROKOW_DLA_ANIMACJI_OBROT;

    for (int i = 0; i < LICZBA_KROKOW_DLA_ANIMACJI_OBROT; ++i) {
        aktywnyDron->rotacja(katKrok);

        // Ważne: dla rotacji też musimy sprawdzić, gdyż
        // rotacja odbywa się względem środka głównego obiektu (drona, bez śrób),
        // natomiast okrąg na podstawie którego sprawdzamy kolizje jest opisany na dronie (trapez w płaszczyźnie XY)
        if (sprawdzKolizja()) {
            aktywnyDron->rotacja(-katKrok);
            std::cout << "Kolizja!" << std::endl;
            return;
        }

        gnutplotApi.redraw();
        std::this_thread::sleep_for(std::chrono::milliseconds(CZAS_TRWANIA_POJEDYNCZEGO_KROKU_OBROT));
    }
}

void Silnik::wykonajRuchDrona(double kat, double odleglosc)
{
    // mały krok, tak żeby nie bylo sytuacji, że dron "przeskoczy" przeszkodę
    const int liczbaKrokow = odleglosc / 0.2;

    double odlKrok = odleglosc / liczbaKrokow;

    double przesuniecieZ = odleglosc * sin(kat * M_PI/180);
    bool czyWDol = przesuniecieZ < -0.000001;

    for (int i = 0; i < liczbaKrokow; ++i) {
        aktywnyDron->wykonajRuch(kat, odlKrok);

        if (sprawdzKolizja()) {
            aktywnyDron->wykonajRuch(kat, -odlKrok);
            std::cout << "Kolizja!" << std::endl;
            return;
        }

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
        std::this_thread::sleep_for(std::chrono::milliseconds(CZAS_TRWANIA_POJEDYNCZEGO_KROKU_RUCH));
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

    ustawAktywnegoDrona(DronId::Czerwony);
}

bool Silnik::sprawdzKolizja() const
{
    for (auto o : przeszkody) {
        if (o->czyKolizja(aktywnyDron)) {
            return true;
        }
    }
    for (auto d : drony) {
        if (d.get() == aktywnyDron) {
            continue;
        }
        if (d->czyKolizja(aktywnyDron)) {
            return true;
        }
    }
    return false;
}

Dron *Silnik::dron(Silnik::DronId id)
{
    return drony.at(static_cast<int>(id) - 1).get();
}
