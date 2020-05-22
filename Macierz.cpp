#include "Macierz.hh"

//funkcja mnożąca macierz przez wektor
Wektor Macierz::operator*(Wektor W)
{
    Wektor Wynik;
    
    for (int i=0; i<3; i++)
    {
        Wynik[i]=0;
    }

    for (int i =0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            Wynik[i]=Wynik[i]+(W[j]*tab[i][j]);
        }
    }
    return Wynik;
}

//funkcja mnożąca macierz razy macierz
Macierz Macierz::operator*(Macierz M)
{
    Macierz Wynik;

    for (int i =0 ; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            for (int l=0; l<3; l++)
            {
                Wynik[i][j]=Wynik[i][j]+(M[j][l]*tab[i][l]);
            }
        }
    }
    return Wynik;
}