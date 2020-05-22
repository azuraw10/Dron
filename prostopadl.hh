#ifndef PROSTOPADL_HH
#define PROSTOPADL_HH

#include "iostream"

//klasa ogólna do prostopadłościana 
class prostopad
{
    float a,b,c;

    public:
    prostopad(float dlpodst, float szpodst, float wysokosc)
    {
        a=dlpodst;
        b=szpodst;
        c=wysokosc;
    }
};

#endif