#include "sroba.h"

Sroba::Sroba(double x, double y, double z, double a, double H)
{
    wierzcholki.resize(12);

    std::vector<Wektor> gornaPodstawa;

    S[0]=x;
    S[1]=y;
    S[2]=z;

    double zDolnej = z - H / 2;
    double zGornej = z + H / 2;

    // Musimy wyznaczyć położenia tylko 2 wierzchołków.
    // Reszte wyznaczamy na podstawie tych 2
    // W1  ___
    //    /   \
    //W0 /     \
    //   \     /
    //    \___/
    //
    double h = a * sqrt(3) / 2;
    double x0 = S[0] - a;
    double y0 = S[1];
    double x1 = S[0] - 0.5 * a;
    double y1 = S[1] + h;

    wierzcholki[0][0] = x0;
    wierzcholki[0][1] = y0;
    wierzcholki[0][2] = zDolnej;

    wierzcholki[1][0] = x1;
    wierzcholki[1][1] = y1;
    wierzcholki[1][2] = zDolnej;

    wierzcholki[2] = wierzcholki[1];
    wierzcholki[2][0] += a;

    wierzcholki[3] = wierzcholki[0];
    wierzcholki[3][0] += 2 * a;

    wierzcholki[4] = wierzcholki[2];
    wierzcholki[4][1] -= 2 * h;

    wierzcholki[5] = wierzcholki[1];
    wierzcholki[5][1] -= 2 * h;

    for (uint i = 0; i < 6; ++i) {
      wierzcholki[i][2] = zDolnej;
    }

    for (uint i = 6; i < 12; ++i) {
      wierzcholki[i] = wierzcholki[i - 6];
      wierzcholki[i][2] = zGornej;
    }
}

Wektor Sroba::srodek()
{

}

std::vector<std::pair<uint, uint> > Sroba::powierzchnie() const
{
    return { {0, 5}, {6, 11}};
}

double Sroba::kierunek() const
{
    return {};
}
