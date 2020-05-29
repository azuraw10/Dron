#include "prostopadloscian.h"

#include "prostopadloscian.h"
#include "math.h"

Prostopadloscian::Prostopadloscian(drawNS::APIGnuPlot3D *gnuplotAPI, int x, int y, int z, float a, float b, float c)
    : ObiektZMozliwosciaRuchuIRotacji(gnuplotAPI)
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
}

double Prostopadloscian::kierunekXY() const
{
    const Wektor w1 = wierzcholki[0];
    const Wektor w2 = wierzcholki[1];
    double delta_x = w1[0] - w2[0];
    double delta_y = w1[1] - w2[1];
    double theta_radians = atan2(delta_y, delta_x);
    return theta_radians;
}

Wektor Prostopadloscian::srodekDlaGlownego()
{
    Wektor w;
    w[0] = (wierzcholki[0][0] + wierzcholki[2][0]) / 2;
    w[1] = (wierzcholki[0][1] + wierzcholki[2][1]) / 2;
    w[2] = (wierzcholki[0][2] + wierzcholki[5][2]) / 2;
    return w;
}

std::vector<std::pair<uint, uint> > Prostopadloscian::powierzchnie() const
{
    return { {0, 3}, {4, 7}};
}

double Prostopadloscian::zDlaDolnejPodstawy() const
{
    return wierzcholki[0][2];
}

