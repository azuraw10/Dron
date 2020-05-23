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
    // przekazujemy wskaźnik do APIGnuPlot3D, tak żeby obiekt miał pełną kontolę odnośnie rysowania
    Obiekt(drawNS::APIGnuPlot3D *gnuplotAPI);

    // zwraca powierzchnie, która jest wykorzystywana podczas dodawania obiektu do gnuplota za pomocą draw_surface
    virtual std::vector<std::vector<Point3D> > surface() const = 0;

    // aktuaizuje położenie obiekty w gnuplocie
    virtual void aktualizuj();

    // usuwa obiekt z gnyplota
    virtual void usunZGnuPlota();

    void ustawKolor(const std::string &kolor);

private:
    drawNS::APIGnuPlot3D *gnuplotAPI;
    int id = -1;
    std::string kolor = "black";
};

#endif // OBIEKT_H
