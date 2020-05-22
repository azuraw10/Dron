#ifndef WEKTOR_HH
#define WEKTOR_HH


#include <iostream>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;

// klasa Wektor wykorzystywana w macierzy(plik skopiowany z poprzedniej pracy)
class Wektor {
  public:
  Wektor operator + (const Wektor & W2) const;
  Wektor operator - (const Wektor & W2) const;
  double operator * (const Wektor & W2) const;

  Wektor operator * (double li) const;

  bool operator == (const Wektor & W2) const;
  bool operator != (const Wektor & W2) const;
  
  
  double dlugosc() const;
  
  
  const double & operator[] (int index) const;
  double & operator[] (int index);    

private:
  double tab[3];

};

Wektor operator * (double l1, Wektor W2);

/*
 * To przeciazenie trzeba opisac. Co ono robi. Jaki format
 * danych akceptuje. Jakie jest znaczenie parametrow itd.
 * Szczegoly dotyczace zalecen realizacji opisow mozna
 * znalezc w pliku:
 *    ~bk/edu/kpo/zalecenia.txt 
 */
std::istream& operator >> (std::istream &Strm, Wektor &Wek);

/*
 * To przeciazenie trzeba opisac. Co ono robi. Jaki format
 * danych akceptuje. Jakie jest znaczenie parametrow itd.
 * Szczegoly dotyczace zalecen realizacji opisow mozna
 * znalezc w pliku:
 *    ~bk/edu/kpo/zalecenia.txt 
 */
std::ostream& operator << (std::ostream &Strm, const Wektor &Wek);


#endif
