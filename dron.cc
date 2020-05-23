#include "dron.hh"
#include "math.h"

Dron::Dron(int x, int y, int z, float a, float b, float c)
    :Prostopad(a,b,c)
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
void Dron::licz_wierzcholki(const Wektor &trans)
{                                               
    for (uint i = 0; i < wierzcholki.size(); ++i) {
        wierzcholki[i] = wierzcholki[i] + trans;
    }
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
    // obrotZ zaklada, że obrót jest wykonywany względem punktu (0,0)
//    const Macierz m = obrotZ(kat);
//    for (uint i = 0; i < wierzcholki.size(); ++i) {
//        wierzcholki[i] = m * wierzcholki[i];
//    }

    for (uint i = 0; i < wierzcholki.size(); ++i) {
        double nowyX = (wierzcholki[i][0] - S[0]) * cos(kat * M_PI/180) - (wierzcholki[i][1] - S[1]) * sin(kat * M_PI/180) + S[0];
        double nowyY = (wierzcholki[i][0] - S[0]) * sin(kat * M_PI/180) + (wierzcholki[i][1] - S[1]) * cos(kat * M_PI/180) + S[1];
        wierzcholki[i][0] = nowyX;
        wierzcholki[i][1] = nowyY;
    }
}

void Dron::wykonajRuch(double kat, double odleglosc)
{
    // Wyznaczamy wektor przesuniącia
    // 1. Wyznaczamy przesunięcie w 2D (w płaszczyźnie XY).
    double przesuniecieXY = odleglosc * cos(kat * M_PI/180);

    // 2. Określamy pod jakim kątem będzie poruszał się dron w płaszczyźnie XY
    const Wektor w1 = wierzcholki[0];
    const Wektor w2 = wierzcholki[1];
    double delta_x = w1[0] - w2[0];
    double delta_y = w1[1] - w2[1];
    double theta_radians = atan2(delta_y, delta_x);
    double przesuniecieX = przesuniecieXY * cos(theta_radians);
    double przesuniecieY = przesuniecieXY * sin(theta_radians);

    // 3. Wyznaczamy przesunięcie w osi Z
    double przesuniecieZ = odleglosc * sin(kat * M_PI/180);

    Wektor w;
    w[0] = przesuniecieX;
    w[1] = przesuniecieY;
    w[2] = przesuniecieZ;

    licz_wierzcholki(w);

    zaktualizujSrodek();
}

void Dron::zaktualizujSrodek()
{
    S[0] = (wierzcholki[0][0] + wierzcholki[2][0]) / 2;
    S[1] = (wierzcholki[0][1] + wierzcholki[2][1]) / 2;
    S[2] = (wierzcholki[0][2] + wierzcholki[5][2]) / 2;
}
