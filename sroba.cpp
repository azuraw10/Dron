#include "sroba.h"

Sroba::Sroba(double x, double y, double z, double a, double H)
{
    wierzcholki.resize(12);

    std::vector<Wektor> gornaPodstawa;

    S[0]=x;
    S[1]=y;
    S[2]=z;

    double zDolnej = z - H/2.0;
    double zGornej = z + H/2.0;

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

std::vector<std::vector<drawNS::Point3D> > Sroba::surface() const
{
    auto createSurface = [this](const std::vector<uint> &indeksy) -> std::vector<drawNS::Point3D> {
        std::vector<drawNS::Point3D> vec;
        for (int index : indeksy) {
            vec.push_back(wierzcholki[index]);
        }
        return vec;
    };

    std::vector<uint> indeksyDlaDolnejPowierzchni;
    for (uint i = 0; i < 6; ++i) {
        indeksyDlaDolnejPowierzchni.push_back(i);
    }
    indeksyDlaDolnejPowierzchni.push_back(0);

    std::vector<uint> indeksyDlaGornejPowierzchni;
    for (uint i = 6; i < 12; ++i) {
        indeksyDlaGornejPowierzchni.push_back(i);
    }
    indeksyDlaGornejPowierzchni.push_back(6);


    return { createSurface(indeksyDlaDolnejPowierzchni), createSurface(indeksyDlaGornejPowierzchni) };
}

void Sroba::licz_wierzcholki(const Wektor &S)
{

}

void Sroba::rotacja(double kat)
{

}

void Sroba::wykonajRuch(double kat, double odleglosc)
{

}

void Sroba::zaktualizujSrodek()
{

}
