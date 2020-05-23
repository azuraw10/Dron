#ifndef SROBA_H
#define SROBA_H

#include "obiektzmozliwosciaruchuirotacji.h"

// Sroba jest reprezentowana przez graniastosłop z sześciokątem foremynm w podstawie
class Sroba : public ObiektZMozliwosciaRuchuIRotacji
{
public:
    // a - bok szesciakata formnego
    Sroba(const Point3D &p, double a, double H);

private:
    Wektor srodek() override;
    std::vector<std::pair<uint, uint>> powierzchnie() const override;

    double kierunekXY() const override;
};

#endif // SROBA_H
