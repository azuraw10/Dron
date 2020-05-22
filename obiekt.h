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

protected:
    // Funkcja wyonuje rotacje punktów z vec względem puntu center o kąt.
    // Rotacja odbywa się względem osi Z.
    void rotacjaZ(std::vector<Wektor> *vec, const Point3D &center, double kat) const;
};

#endif // OBIEKT_H
