#include "obiektzmozliwosciaruchuirotacji.h"

ObiektZMozliwosciaRuchuIRotacji::ObiektZMozliwosciaRuchuIRotacji()
{

}

//w tej funkcji chciałem aktualizować współrzędne wektorów
//nie wiem jak się odwołać do poszczególnego wektora natomiast wydaje mi się, że (*this) powinno wystarczyć
void ObiektZMozliwosciaRuchuIRotacji::licz_wierzcholki(const Wektor &trans)
{
    for (uint i = 0; i < wierzcholki.size(); ++i) {
        wierzcholki[i] = wierzcholki[i] + trans;
    }
}

void ObiektZMozliwosciaRuchuIRotacji::rotacja(double kat)
{
    // obrotZ zaklada, że obrót jest wykonywany względem punktu (0,0)
//    const Macierz m = obrotZ(kat);
//    for (uint i = 0; i < wierzcholki.size(); ++i) {
//        wierzcholki[i] = m * wierzcholki[i];
//    }

    for (uint i = 0; i < wierzcholki.size(); ++i) {
        double nowyX = (wierzcholki[i][0] - S[0]) * cos(kat * M_PI/180) - (wierzcholki[i][1] - S[1]) * sin(kat * M_PI/180) + S[0];
        double nowyY = (wierzcholki[i][0] - S[0]) * sin(kat * M_PI/180) + (wierzcholki[i][1] - S[1]) * cos(kat * M_PI/180) + S[1];
        wierzcholki[i][0] = nowyX;
        wierzcholki[i][1] = nowyY;
    }
}

void ObiektZMozliwosciaRuchuIRotacji::wykonajRuch(double kat, double odleglosc)
{
    // Wyznaczamy wektor przesuniącia
    // 1. Wyznaczamy przesunięcie w 2D (w płaszczyźnie XY).
    double przesuniecieXY = odleglosc * cos(kat * M_PI/180);

    // 2. Określamy pod jakim kątem będzie poruszał się dron w płaszczyźnie XY
    double theta_radians = kierunek();
    double przesuniecieX = przesuniecieXY * cos(theta_radians);
    double przesuniecieY = przesuniecieXY * sin(theta_radians);

    std::cout << "AAA" << theta_radians;

    // 3. Wyznaczamy przesunięcie w osi Z
    double przesuniecieZ = odleglosc * sin(kat * M_PI/180);

    Wektor w;
    w[0] = przesuniecieX;
    w[1] = przesuniecieY;
    w[2] = przesuniecieZ;

    licz_wierzcholki(w);

    S = srodek();
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
