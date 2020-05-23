#include "Wektor.hh"

int Wektor::liczbaStworzonych = 0;
int Wektor::liczbaIstniejacych = 0;

//plik stworzony do wcześniejszego programu
//służy do liczenia wektorów
Wektor::Wektor()
{
    ++liczbaStworzonych;
    ++liczbaIstniejacych;
}

Wektor::Wektor(const Wektor &w)
{
    ++liczbaStworzonych;
    ++liczbaIstniejacych;

    // Ponieważ piszemy wlasny kosntruktor kopiujący, musimy wykonać kopiowanie.
    // Tutaj innym podejście może być dodanie klasy licznik jako klasy bazowej,
    // najlepiej jako szablon, tak żeby można było użyć licznika dla różnych klas.
    // Ale ponieważ tutaj musimy skopiować tylko tab, więc dodanie 3 dodatkowych linii do nie problem.

    for (uint i = 0; i < 3; ++i) {
        tab[i] = w.tab[i];
    }
}

Wektor::~Wektor()
{
    --liczbaIstniejacych;
}

Wektor Wektor::operator + (const Wektor & W2) const
{
    Wektor Wynik;

    for (int i=0; i<3; i++)
    {
        Wynik[i]=tab[i]+W2[i];
    }
    return Wynik;
}

Wektor Wektor::operator - (const Wektor & W2) const
  {
      Wektor Wynik;

      for (int i=0; i<3; i++)
      {
      Wynik[i]=tab[i]-W2[i];
      }
      return Wynik;
  }

double Wektor::operator * (const Wektor & W2) const
{
    double Wynik;

    for (int i=0; i<3; i++)
    {
        Wynik = Wynik + (tab[i]*W2[i]);
    }
    return Wynik;
}

Wektor Wektor::operator * (double l1) const
  {
    Wektor Wynik;
      
      for (int i=0; i<3; i++)
      {
          Wynik[i]=tab[i]*l1;
      }
    return Wynik;
  }

  bool Wektor::operator == (const Wektor & W2) const
  {
    for (int i=0; i<3; i++)
      {
          if(abs(tab[i]-W2[i]) >= 0.000001)
            return false;
      }
    return true;
  }

  bool Wektor::operator != (const Wektor & W2) const
  {
    for (int i=0; i<3; i++)
      {
          if(tab[i] == W2[i])
            return false;
      }
    return true;
  }

  double Wektor::dlugosc() const
    {
    double dlugosc;

    for (int i=0; i<3; i++ )
        {
        dlugosc =  dlugosc + pow(tab[i], 2);
        }

    dlugosc = pow(dlugosc, (1/2));

    return dlugosc;
    }

double & Wektor::operator[] (int index)
{
    if (index < 0 || index >= 3) 
    {
      std::cerr << "poza zakresem" << std::endl;
      exit(1);
    }

    return tab[index];
}

int Wektor::liczbaStworzonychObiektow()
{
    return liczbaStworzonych;
}

int Wektor::liczbaIstniejacychObiektow()
{
    return liczbaIstniejacych;
}

const double & Wektor::operator[] (int index) const
{
    if (index < 0 || index >= 3) 
    {
      std::cerr << "poza zakresem" << std::endl;
      exit(1);
    }

    return tab[index];
}

std::ostream& operator << (std::ostream &Strm, const Wektor &Wek)
{
    for (int i=0; i<3; i++)
    {
        Strm << Wek[i];
        return Strm;
    }
}

std::istream& operator >> (std::istream &Strm, Wektor &Wek)
{
    for (int i=0; i<3; i++)
    {
        Strm >> Wek[i];
        return Strm;
    }
}

Wektor operator * (Wektor W2, double l1)
{
    Wektor Wynik;

    for (int i=0; i<3; i++)
    {
        Wynik[i]=W2[i]*l1;
    }
    return Wynik;
}
