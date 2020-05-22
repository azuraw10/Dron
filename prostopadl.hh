#ifndef PROSTOPADL_HH
#define PROSTOPADL_HH

#include "iostream"

//klasa ogólna do prostopadłościana 
class Prostopad
{
    float a,b,c;

    public:
    Prostopad(float dlpodst, float szpodst, float wysokosc)
    {
        a=dlpodst;
        b=szpodst;
        c=wysokosc;
    }
};

#endif
