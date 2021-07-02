#ifndef OBJECT
#define OBJECT

#include <bits/stdc++.h>
using namespace std;

class Object
{
protected:
    
    double coEfficients[4];
    int shine;

public:
double color[3];
    virtual void draw() = 0;

    void setColor(double color[])
    {
        for(int i = 0; i < 3; i++) this->color[i] = color[i];
    }
    void setCoEfficients(double coEfficients[])
    {
        for(int i = 0; i < 3; i++) this->coEfficients[i] = coEfficients[i];
    }
    void setShine(int shine) { this->shine = shine; }
};

#endif