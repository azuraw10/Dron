#ifndef OBIEKTZMOZLIWOSCIARUCHUIROTACJI_H
#define OBIEKTZMOZLIWOSCIARUCHUIROTACJI_H

#include "obiekt.h"

class ObiektZMozliwosciaRuchuIRotacji : public Obiekt
{
public:
    ObiektZMozliwosciaRuchuIRotacji();

    void rotacja(double kat);

    void wykonajRuch(double kat, double odleglosc);

    std::vector<std::vector<Point3D> > surface() const override;

protected:
    virtual Wektor srodek() = 0;
    virtual double kierunek() const = 0;
    virtual std::vector<std::pair<uint, uint>> powierzchnie() const = 0;

    std::vector<Wektor> wierzcholki;
    Wektor S;

private:
    //funkcja wyliczająca wektory wierzcholkow
    void licz_wierzcholki(const Wektor &S);
};

#endif // OBIEKTZMOZLIWOSCIARUCHUIROTACJI_H
