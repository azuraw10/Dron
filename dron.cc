#include "dron.hh"
#include "math.h"

static const double HSroby = 1;

Dron::Dron(drawNS::APIGnuPlot3D *gnuplotAPI, int x, int y, int z, float a, float b, float c)
    : Prostopadloscian(gnuplotAPI, x, y, z, a, b, c)
{
    // Wyznaczam bok dla śrób - sróby powinny nie być za duże w stosunku do drona
    double bokSroby = std::min(c, b) / 3;
    Wektor w;
    w[0] = HSroby / 2;
    // Dodaj sroby z "tyłu" drona
    auto s1 = std::unique_ptr<Sroba>(new Sroba(gnuplotAPI, wierzcholki[2] + w, bokSroby, HSroby));
    s1->ustawKolor("green");
    // musimy przenieść, żeby uniknąć błędów kompilacji
    obiektyZalezne.push_back(std::move(s1));

    auto s2 = std::unique_ptr<Sroba>(new Sroba(gnuplotAPI, wierzcholki[1] + w, bokSroby, HSroby));
    s2->ustawKolor("green");
    obiektyZalezne.push_back(std::move(s2));
}

Prostopadloscian::PunktXY Dron::srodek() const
{
    // drona możemy traktować jako trapez równoramienny, na płaszczyźnie XY

    const double R = promien();

    const PunktXY a = wierzcholki[0];
    const PunktXY d = wierzcholki[3];

    const PunktXY srodekGornejPodstawy = PunktXY( (a.x + d.x) / 2, ( a.y + d.y ) / 2);

    const Wektor w1 = wierzcholki[0];
    const Wektor w2 = wierzcholki[1];
    double delta_x = a.x - d.x;
    double delta_y = a.y - d.y;
    double theta_radians = atan2(delta_y, delta_x);
    theta_radians += 90 * M_PI/180;

    double x = srodekGornejPodstawy.x + cos(theta_radians) * R;
    double y = srodekGornejPodstawy.y + sin(theta_radians) * R;

    return {x, y};
}

double Dron::promien() const
{
    // drona możemy traktować jako trapez równoramienny, na płaszczyźnie XY

    const PunktXY a = wierzcholki[0];
    const PunktXY d = wierzcholki[3];

    const Sroba *srobaB = dynamic_cast<Sroba*>(obiektyZalezne[1].get());
    const Sroba *srobaC = dynamic_cast<Sroba*>(obiektyZalezne[0].get());

    const PunktXY b = srobaB->wierzcholki[11];
    const PunktXY c = srobaC->wierzcholki[7];

    double dlGornejPodstawy = sqrt(pow(a.x - d.x, 2) + pow(a.y - d.y, 2));
    double dlDolnejPodstawy = sqrt(pow(b.x - c.x, 2) + pow(b.y - c.y, 2));

    // wzór wzięty z internetu
    double R = sqrt(( dlGornejPodstawy * dlDolnejPodstawy + pow( dlDolnejPodstawy + dlGornejPodstawy, 2) / 4) *
                    pow( (dlDolnejPodstawy + dlGornejPodstawy) / 2, 2 ) / (4 * dlGornejPodstawy * dlDolnejPodstawy));

    return R;
}

