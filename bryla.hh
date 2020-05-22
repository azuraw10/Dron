#ifndef BRYLA_HH
#define BRYLA_HH

#include <iostream>
#include <math.h>
#include "Wektor.hh"
#include "Macierz.hh"

#define PI 3.14159265

//klasa mająca na celu pilnowanie orientacji bryły/prostopadloscianu/drona
class Bryla
{
public:
    //konstruktor który daje na przekątnej wartości 1 czyli początkową orientację
    Bryla()
    {
        for (int i=0; i<3; i++)
        {
            for (int j=0; j<3 ;j++)
            {
                if (i==j)
                {
                    orient[i][j]=1;
                }
                else 
                {
                    orient[i][j]=0;
                }
            }
        }
    }

    //funkcja wykonująca obrót o podany kąt
    Macierz obrotZ(double kat);

protected:
    Macierz orient;
};

#endif
