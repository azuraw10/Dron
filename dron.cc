#include "dron.hh"

//W tej funkcji chciałem stworzyć dostęp do wektorów w klasie dron
// nie wiem jak zrobić to sprytniej
//wyskakuje błąd z stringiem, że jest niezdefiniowany
Wektor dron::operator [](std::string i)
{
    if (i=="A")
        return A;
    else if (i=="B")
        return B;
    else if (i=="C")
        return C;
    else if (i=="D")
        return D;
    else if (i=="E")
        return E;
    else if (i=="F")
        return F;
    else if (i=="G")
        return G;

    return {};
}

//w tej funkcji chciałem aktualizować współrzędne wektorów
//nie wiem jak się odwołać do poszczególnego wektora natomiast wydaje mi się, że (*this) powinno wystarczyć
Wektor dron::licz_wierzcholki(const Wektor trans)   
{                                               
    Wektor Wynik;

    //Wynik=orient*(*this)+trans; //orient pochodzi z klasy bryla, natomiast trans będzie wyliczane na podstawie cos i sin w razie jakby płynął pod kątem
    return Wynik;
}

Wektor dron::getA() const
{
    return A;
}
