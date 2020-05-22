#include "dron.hh"

//W tej funkcji chciałem stworzyć dostęp do wektorów w klasie dron
// nie wiem jak zrobić to sprytniej
//wyskakuje błąd z stringiem, że jest niezdefiniowany
dron::dron(int x, int y, int z, float a, float b, float c)
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

//w tej funkcji chciałem aktualizować współrzędne wektorów
//nie wiem jak się odwołać do poszczególnego wektora natomiast wydaje mi się, że (*this) powinno wystarczyć
Wektor dron::licz_wierzcholki(const Wektor trans)   
{                                               
    Wektor Wynik;

    //Wynik=orient*(*this)+trans; //orient pochodzi z klasy bryla, natomiast trans będzie wyliczane na podstawie cos i sin w razie jakby płynął pod kątem
    return Wynik;
}

std::vector<std::vector<drawNS::Point3D> > dron::surface() const
{
    return { {A, B, C, D, A }, { E, F, G, H, E } };
}
