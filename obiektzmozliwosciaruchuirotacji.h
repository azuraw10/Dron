#ifndef OBIEKTZMOZLIWOSCIARUCHUIROTACJI_H
#define OBIEKTZMOZLIWOSCIARUCHUIROTACJI_H

#include "obiekt.h"

#include "licznik.h"

class ObiektZMozliwosciaRuchuIRotacji : public Obiekt, public Licznik<ObiektZMozliwosciaRuchuIRotacji>
{
public:
    ObiektZMozliwosciaRuchuIRotacji(drawNS::APIGnuPlot3D *gnuplotAPI);

    // Obracamy obiekt o dany kąt względem osi OZ
    // Punktem odniesienia jest środek obiektu
    void rotacja(double kat);

    // Obracamy obiekt o dany kąt względem osi OZ
    // Punkt odniesienia jest podawnay jako drugi parameter funkcji
    void rotacja(double kat, const Point3D &punktOdniesienia);

    // Wykonujemy ruch obiektem o zadany kąt i odległość
    void wykonajRuch(double kat, double odleglosc);

    std::vector<std::vector<Point3D> > surface() const override;

    void aktualizuj() override;

    void usunZGnuPlota() override;

    void ustawKolor(const std::string &kolor) override;

    // zmienia wartość Z dla każdego z wierzcholłków o zadaną wartość
    void zmienZDlaDolnejPodstawyOWartosc(double z);

    // zwraca wartość Z dla punktu położenego najniżej
    double minZ() const;

    // zwraca wartość Z dla punktu położenego najwyżej
    double maxZ() const;

protected:
    virtual Wektor srodekDlaGlownego() const = 0;

    // Zwraca kąt w radianch, który określa w którą stronę powinien poruszać się dron
    virtual double kierunekXY() const = 0;
    // Zwraca "powierzchnie", na podsawie których konstruowany jest obiekt,
    // a konkretniej - zwracany wektor zawiera pary {indeks_początkowym indeks_końcowy}
    // i na podstawie tych indeksów jest tworzona powierzchnia w funkcji surface,
    // np. dla indeksów 1 i 3, powierzhcnia jest budowana na podstawie
    // następujących wierzchołków 1,2,3,1 - na końcu dodawany jest indeks początkowy tak, żeby zamknąć figurę
    virtual std::vector<std::pair<uint, uint>> powierzchnie() const = 0;

    std::vector<Wektor> wierzcholki;
    Wektor S;

    // tutaj możemy przechowywać jakieś zależne obiekty da obiekt głównego:
    // np. Główny obiektem jest dron, a sróby są obiektami zależanymi
    std::vector<std::unique_ptr<ObiektZMozliwosciaRuchuIRotacji>> obiektyZalezne;

private:
    //funkcja wyliczająca wektory wierzcholkow
    void licz_wierzcholki(const Wektor &S);
};

#endif // OBIEKTZMOZLIWOSCIARUCHUIROTACJI_H
