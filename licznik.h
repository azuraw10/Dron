#ifndef LICZNIK_H
#define LICZNIK_H

template <class T>
class Licznik
{
public:
    Licznik()
    {
        ++liczbaStworzonych;
        ++liczbaIstniejacych;
    }
    Licznik(const Licznik &)
    {
        ++liczbaStworzonych;
        ++liczbaIstniejacych;
    }
    ~Licznik()
    {
        --liczbaIstniejacych;
    }

    static int liczbaStworzonychObiektow()
    {
        return liczbaStworzonych;
    }
    static int liczbaIstniejacychObiektow()
    {
        return liczbaIstniejacych;
    }

private:
    static int liczbaStworzonych;
    static int liczbaIstniejacych;
};

template <typename T>
int Licznik<T>::liczbaStworzonych = 0;

template <typename T>
int Licznik<T>::liczbaIstniejacych = 0;

#endif // LICZNIK_H
