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

Wektor Prostopadloscian::srodekDlaGlownego() const
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

Prostopadloscian::PunktXY Prostopadloscian::srodek() const
{
    return srodekDlaGlownego();
}

double Prostopadloscian::promien() const
{
    PunktXY a = wierzcholki[0];
    PunktXY b = wierzcholki[1];
    PunktXY c = wierzcholki[2];

    double dlBokuA = PunktXY::odleglosc(a, b);
    double dlBokuB = PunktXY::odleglosc(a, c);

    double R = sqrt(pow(0.5 * dlBokuA, 2) + pow(0.5 * dlBokuB, 2) );

    return R;
}

bool Prostopadloscian::czyKolizja(Prostopadloscian *obiekt)
{
    double zMax1 = maxZ();
    double zMax2 = obiekt->maxZ();

    double zMin1 = minZ();
    double zMin2 = obiekt->minZ();

    // sprawdzamy kolizje jeśli obiekty przecinają się w osi Z
    if (zMax2 < zMin1) {
        return false;
    }

    if (zMin2 > zMax1) {
        return false;
    }

    PunktXY srodek1 = srodek();
    PunktXY srodek2 = obiekt->srodek();

    double R1 = promien();
    double R2 = obiekt->promien();

    double odlegloscOdSrodkow = PunktXY::odleglosc(srodek1, srodek2);

    return (odlegloscOdSrodkow < R1 + R2);
}


Prostopadloscian::PunktXY::PunktXY(double x, double y)
    : x(x), y(y)
{

}

Prostopadloscian::PunktXY::PunktXY(const Wektor &wektor)
{
    x = wektor[0];
    y = wektor[1];
}

double Prostopadloscian::PunktXY::odleglosc(const Prostopadloscian::PunktXY &a, const Prostopadloscian::PunktXY &b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
