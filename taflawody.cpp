#include "taflawody.h"

double TaflaWody::wyznaczZ(double x) const
{
    return pobierzZ() + cos(x);
}
