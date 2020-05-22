#include "dron.hh"
#include "math.h"

Dron::Dron(int x, int y, int z, float a, float b, float c)
    :prostopad(a,b,c)
{
    wierzcholki.resize(8);

    S[0]=x;
    S[1]=y;
    S[2]=z;
    wierzcholki[0][0]=-a/2; wierzcholki[0][1]=-b/2;  wierzcholki[0][2]=-c/2;
    wierzcholki[1][0]=a/2;  wierzcholki[1][1]=-b/2;  wierzcholki[1][2]=-c/2;
    wierzcholki[2][0]=a/2;  wierzcholki[2][1]=b/2;   wierzcholki[2][2]=-c/2;
    wierzcholki[3][0]=-a/2; wierzcholki[3][1]=b/2;   wierzcholki[3][2]=-c/2;
    wierzcholki[4][0]=-a/2; wierzcholki[4][1]=-b/2;  wierzcholki[4][2]=c/2;
    wierzcholki[5][0]=a/2;  wierzcholki[5][1]=-b/2;  wierzcholki[5][2]=c/2;
    wierzcholki[6][0]=a/2;  wierzcholki[6][1]=b/2;   wierzcholki[6][2]=c/2;
    wierzcholki[7][0]=-a/2; wierzcholki[7][1]=b/2;   wierzcholki[7][2]=c/2;
}

//w tej funkcji chciałem aktualizować współrzędne wektorów
//nie wiem jak się odwołać do poszczególnego wektora natomiast wydaje mi się, że (*this) powinno wystarczyć
Wektor Dron::licz_wierzcholki(const Wektor trans)
{                                               
    Wektor Wynik;

    //Wynik=orient*(*this)+trans; //orient pochodzi z klasy bryla, natomiast trans będzie wyliczane na podstawie cos i sin w razie jakby płynął pod kątem
    return Wynik;
}

std::vector<std::vector<drawNS::Point3D> > Dron::surface() const
{
    auto createSurface = [this](const std::vector<int> &indeksy) -> std::vector<drawNS::Point3D> {
        std::vector<drawNS::Point3D> vec;
        for (int index : indeksy) {
            vec.push_back(wierzcholki[index]);
        }
        return vec;
    };

    return { createSurface({ 0,1,2,3,0 }), createSurface({ 4,5,6,7,4  }) };
}

void Dron::rotacja(double kat)
{
    rotacjaZ(&wierzcholki, S, kat);
}
