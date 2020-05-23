#include "sroba.h"

Sroba::Sroba(const drawNS::Point3D &p, double a, double H)
{
    wierzcholki.resize(12);

    std::vector<Wektor> gornaPodstawa;

    S[0]=p[0];
    S[1]=p[1];
    S[2]=p[2];

    double zDolnej = p[2] - H / 2;
    double zGornej = p[2] + H / 2;

    /* Musimy wyznaczyć położenia tylko 2 wierzchołków.
    // Reszte wyznaczamy na podstawie tych 2
    // W1  ___
    //    /   \
    //W0 /     \
    //   \     /
    //    \___/
    */
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
    Wektor w;
    w[0] = (wierzcholki[0][0] + wierzcholki[3][0]) / 2;
    w[1] = wierzcholki[0][1];
    w[2] = (wierzcholki[0][2] + wierzcholki[6][2]) / 2;
    return w;
}

std::vector<std::pair<uint, uint> > Sroba::powierzchnie() const
{
    return { {0, 5}, {6, 11}};
}

double Sroba::kierunekXY() const
{
    const Wektor w1 = wierzcholki[0];
    const Wektor w2 = wierzcholki[3];
    double delta_x = w1[0] - w2[0];
    double delta_y = w1[1] - w2[1];
    double theta_radians = atan2(delta_y, delta_x);
    return theta_radians;
}
