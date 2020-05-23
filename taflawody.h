#ifndef TAFLAWODY_H
#define TAFLAWODY_H

#include "powierzchnia.h"

class TaflaWody : public Powierzchnia
{
public:
    // korzystamy z konstruktora z klasy Powierzchnia
    using Powierzchnia::Powierzchnia;

    // Nadpisujemy tę funkcję, ta żeby tafla miał kształ sinusoidy
    double wyznaczZ(double x) const override;
};

#endif // TAFLAWODY_H
