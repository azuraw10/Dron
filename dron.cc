#include "dron.hh"

//W tej funkcji chciałem stworzyć dostęp do wektorów w klasie dron
// nie wiem jak zrobić to sprytniej
//wyskakuje błąd z stringiem, że jest niezdefiniowany
Wektor dron::operator [](string i)
{
    if (i='A')
        return A;
    else if (i='B')
        return B;
    else if (i='C')
        return C;
    else if (i='D')
        return D;
    else if (i='E')
        return E;
    else if (i='F')
        return F;
    else if (i='G')
        return G;
}

//w tej funkcji chciałem aktualizować współrzędne wektorów
Wektor dron::licz_wierzcholki(const Wektor trans)   
{                                               
    Wektor Wynik;

    Wynik=(*this)+S;
    return Wynik;
}