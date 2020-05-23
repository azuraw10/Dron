#ifndef OBIEKT_H
#define OBIEKT_H

#include <vector>
#include "Dr3D_gnuplot_api.hh"
#include "Macierz.hh"
#include "Wektor.hh"

using drawNS::Point3D;

class Obiekt
{
public:
    Obiekt();

    virtual std::vector<std::vector<Point3D> > surface() const = 0;

    void rysuj(drawNS::APIGnuPlot3D *gnuplotAPI);

    void ustawKolor(const std::string &kolor);

private:
    int id = -1;
    std::string kolor = "black";
};

#endif // OBIEKT_H
