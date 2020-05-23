#include "obiektzmozliwosciaruchuirotacji.h"

ObiektZMozliwosciaRuchuIRotacji::ObiektZMozliwosciaRuchuIRotacji(drawNS::APIGnuPlot3D *gnuplotAPI)
    : Obiekt(gnuplotAPI)
{

}

void ObiektZMozliwosciaRuchuIRotacji::rotacja(double kat)
{
    rotacja(kat, S);
}

void ObiektZMozliwosciaRuchuIRotacji::aktualizuj()
{
    Obiekt::aktualizuj();
    for (auto &o : obiektyZalezne) {
        o->aktualizuj();
    }
}

void ObiektZMozliwosciaRuchuIRotacji::usunZGnuPlota()
{
    Obiekt::usunZGnuPlota();
    for (auto &o : obiektyZalezne) {
        o->usunZGnuPlota();
    }
}

//w tej funkcji chciałem aktualizować współrzędne wektorów
//nie wiem jak się odwołać do poszczególnego wektora natomiast wydaje mi się, że (*this) powinno wystarczyć
void ObiektZMozliwosciaRuchuIRotacji::licz_wierzcholki(const Wektor &trans)
{
    for (uint i = 0; i < wierzcholki.size(); ++i) {
        wierzcholki[i] = wierzcholki[i] + trans;
    }
}

void ObiektZMozliwosciaRuchuIRotacji::rotacja(double kat, const drawNS::Point3D &punktOdniesienia)
{
    // obrotZ zaklada, że obrót jest wykonywany względem punktu (0,0)
//    const Macierz m = obrotZ(kat);
//    for (uint i = 0; i < wierzcholki.size(); ++i) {
//        wierzcholki[i] = m * wierzcholki[i];
//    }

    for (uint i = 0; i < wierzcholki.size(); ++i) {
        double nowyX = (wierzcholki[i][0] - punktOdniesienia[0]) * cos(kat * M_PI/180) - (wierzcholki[i][1] - punktOdniesienia[1]) * sin(kat * M_PI/180) + punktOdniesienia[0];
        double nowyY = (wierzcholki[i][0] - punktOdniesienia[0]) * sin(kat * M_PI/180) + (wierzcholki[i][1] - punktOdniesienia[1]) * cos(kat * M_PI/180) + punktOdniesienia[1];
        wierzcholki[i][0] = nowyX;
        wierzcholki[i][1] = nowyY;
    }

    for (auto &o : obiektyZalezne) {
        // punktem obrotu dla srób musi być środek drona
        o->rotacja(kat, S);
    }

    aktualizuj();
}

void ObiektZMozliwosciaRuchuIRotacji::wykonajRuch(double kat, double odleglosc)
{
    // Wyznaczamy wektor przesuniącia
    // 1. Wyznaczamy przesunięcie w 2D (w płaszczyźnie XY).
    double przesuniecieXY = odleglosc * cos(kat * M_PI/180);

    // 2. Określamy pod jakim kątem będzie poruszał się dron w płaszczyźnie XY
    double thetaRadians = kierunekXY();
    double przesuniecieX = przesuniecieXY * cos(thetaRadians);
    double przesuniecieY = przesuniecieXY * sin(thetaRadians);

    // 3. Wyznaczamy przesunięcie w osi Z
    double przesuniecieZ = odleglosc * sin(kat * M_PI/180);

    Wektor w;
    w[0] = przesuniecieX;
    w[1] = przesuniecieY;
    w[2] = przesuniecieZ;

    licz_wierzcholki(w);

    S = srodek();

    for (auto &o : obiektyZalezne) {
        o->wykonajRuch(kat, odleglosc);
    }

    aktualizuj();
}

std::vector<std::vector<drawNS::Point3D> > ObiektZMozliwosciaRuchuIRotacji::surface() const
{
    std::vector<std::vector<drawNS::Point3D> > wynik;

    for (const std::pair<uint, uint> &p : powierzchnie()) {
        std::vector<drawNS::Point3D> vec;
        for (uint i = p.first; i <= p.second; ++i) {
            vec.push_back(wierzcholki[i]);
        }
        vec.push_back(wierzcholki[p.first]);
        wynik.push_back(vec);
    }

    return wynik;
}
