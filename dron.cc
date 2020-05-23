#include "dron.hh"
#include "math.h"

Dron::Dron(drawNS::APIGnuPlot3D *gnuplotAPI, int x, int y, int z, float a, float b, float c)
    : ObiektZMozliwosciaRuchuIRotacji(gnuplotAPI), Prostopad(a,b,c)
{
    wierzcholki.resize(8);

    S[0]=x;
    S[1]=y;
    S[2]=z;

    // przy wyznaczniu wierzcholków korzystamy z współrzędnych pierwszego wierzcholka
    wierzcholki[0][0]=x-a/2; wierzcholki[0][1]=y-b/2;  wierzcholki[0][2]=z-c/2;

    wierzcholki[1] = wierzcholki[0];
    wierzcholki[1][0] += a;

    wierzcholki[2] = wierzcholki[1];
    wierzcholki[2][1] += b;

    wierzcholki[3] = wierzcholki[0];
    wierzcholki[3][1] += b;

    for (int i = 4; i < 8; ++i) {
        wierzcholki[i] = wierzcholki[i - 4];
        wierzcholki[i][2] += c;
    }

    // Wyznaczam bok dla śrób - sróby powinny nie być za duże w stosunku do drona
    double bokSroby = std::min(a, b) / 3;
    // Dodaj sroby z "tyłu" drona
    auto s1 = std::unique_ptr<Sroba>(new Sroba(gnuplotAPI, wierzcholki[6],bokSroby,0.5));
    s1->ustawKolor("green");
    // musimy przenieść, żeby uniknąć błędów kompilacji
    obiektyZalezne.push_back(std::move(s1));

    auto s2 = std::unique_ptr<Sroba>(new Sroba(gnuplotAPI, wierzcholki[5],bokSroby,0.5));
    s2->ustawKolor("green");
    obiektyZalezne.push_back(std::move(s2));
}

double Dron::kierunekXY() const
{
    const Wektor w1 = wierzcholki[0];
    const Wektor w2 = wierzcholki[1];
    double delta_x = w1[0] - w2[0];
    double delta_y = w1[1] - w2[1];
    double theta_radians = atan2(delta_y, delta_x);
    return theta_radians;
}

Wektor Dron::srodek()
{
    Wektor w;
    w[0] = (wierzcholki[0][0] + wierzcholki[2][0]) / 2;
    w[1] = (wierzcholki[0][1] + wierzcholki[2][1]) / 2;
    w[2] = (wierzcholki[0][2] + wierzcholki[5][2]) / 2;
    return w;
}

std::vector<std::pair<uint, uint> > Dron::powierzchnie() const
{
    return { {0, 3}, {4, 7}};
}

double Dron::zDlaDolnejPodstawy() const
{
    return wierzcholki[0][2];
}

