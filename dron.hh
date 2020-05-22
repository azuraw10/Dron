#ifndef DRON_HH
#define DRON_HH

#include <iostream>
#include "prostopadl.hh"
#include "Wektor.hh"
#include "bryla.hh"
#include "Macierz.hh"

//clasa dron dziedziczy z prostopad długości boków oraz z bryly orientacje
// metody na wyliczenie orientacji są w bryle, natomiast w tej klasie jest metoda na wyliczanie wierzcholkow po ruchu
class dron :public prostopad, public bryla
{
    Wektor A,B,C,D,E,F,G,H;//abcd podstawa efgh górna podstawa
    Wektor S;
    
    public:
    //konstruktor w którym wyznaczam zależności współrzędnych każdego punktu w zależności punktu S
    dron(int x=0, int y=0, int z=0, float a=2, float b=2, float c=2) 
    :prostopad(a,b,c)
    {
        S[0]=x;
        S[1]=y;
        S[2]=z;
        A[0]=-a/2;  A[1]=-b/2;  A[2]=-c/2;
        B[0]=a/2;  B[1]=-b/2;   B[2]=-c/2;
        C[0]=a/2;  C[1]=b/2;    C[2]=-c/2;
        D[0]=-a/2;  D[1]=b/2;   D[2]=-c/2;
        E[0]=-a/2;   E[1]=-b/2;   E[2]=c/2;
        F[0]=a/2;   F[1]=-b/2;   F[2]=c/2;
        G[0]=a/2;   G[1]=b/2;   G[2]=c/2;
        H[0]=-a/2;   H[1]=b/2;   H[2]=c/2;
    }

    //funkcja która ma odwoływać się do danego wektora
    Wektor operator [](std::string i);
    //funkcja wyliczająca wektory wierzcholkow
    Wektor licz_wierzcholki(const Wektor S);

    Wektor getA() const;
};

#endif
