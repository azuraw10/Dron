#include "bryla.hh"

//obracamy o podany kąt
Macierz Bryla::obrotZ(double kat)
{
    Macierz Wynik, obrot;

    //robimy wzór na macierz odwrotną względem osi Z(wzór znalazłem na wikipedii)
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3 ;j++)
        {
            if ((i==0) && j==0)
            {
                obrot[i][j]=cos(kat*PI/180);
            }
            else if (i==0 && j==1)
            {
                obrot[i][j]=-sin(kat*PI/180);
            }
            else if (i==1 && j==0)
            {
                obrot[i][j]=sin(kat*PI/180);
            }
            else if (i==1 && j==1)
            {
                obrot[i][j]=cos(kat*PI/180);
            }
            else if (i==2 && j==2)
            {
                obrot[i][j]=1;
            }
            else 
            {
                obrot[i][j]=0;
            }
        }
    }

    Wynik=orient*obrot;

    return Wynik;

}
