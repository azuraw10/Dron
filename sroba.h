#ifndef SROBA_H
#define SROBA_H

#include "obiekt.h"

// Sroba jest reprezentowana przez graniastosłop z sześciokątem foremynm w podstawie
class Sroba : public Obiekt
{
public:
    // a - bok szesciakata formnego
    Sroba(double x, double y, double z, double a, double H);

    std::vector<std::vector<Point3D> > surface() const override;

    void licz_wierzcholki(const Wektor &S);

    void rotacja(double kat);

    void wykonajRuch(double kat, double odleglosc);

private:
    void zaktualizujSrodek();

    std::vector<Wektor> wierzcholki;
    Wektor S;
};

#endif // SROBA_H
