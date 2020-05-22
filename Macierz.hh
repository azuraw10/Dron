#ifndef MACIERZ_HH
#define MACIERZ_HH

#include <iostream>
#include "Wektor.hh"

//klasa złożona z tablicy 3 elementowej z Wektorami
class Macierz 
{
    Wektor tab[3];

    public:
    //konstruktor zerujący macierz
    Macierz()
    {
        for (int i=0; i<3; i++)
        {
            for (int j=0; j<3; j++)
            {
                tab[i][j]=0;
            }
        }
    }

    //odwołanie do danego elementu macierzy
    const Wektor & operator[] (int index) const {if(index>3 || index<0){exit(1);}else return tab[index];}
    Wektor & operator[] (int index) {if(index>3 || index<0){exit(1);}else return tab[index];}

    //funkcje które potrzebujemy do obliczenia orientacji i obrotu bryły
    Wektor operator * (Wektor W);
    Macierz operator * (Macierz M);
};

#endif