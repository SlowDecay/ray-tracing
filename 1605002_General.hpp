#ifndef GENERAL
#define GENERAL

class General;

#include <bits/stdc++.h>
#include <GL/glut.h>
#include <windows.h>

#include "1605002_Object.hpp"
#include "1605002_Vector3D.hpp"
#include "1605002_Globals.hpp"

using namespace std;

struct General : public Object
{
public:
    double a, b, c, d, e, f, g, h, i, j;
    Vector3D refPoint;
    double length, width, height;

    General() {}

    virtual void draw()
    {
        return;
    }

    friend istream& operator>>(istream&, General&);
};

istream& operator>>(istream& din, General& g)
{
    din >> g.a >> g.b >> g.c >> g.d >> g.e >> g.f >> g.g >> g.h >> g.i >> g.j;
    din >> g.refPoint >> g.length >> g.width >> g.height;
    for(int i = 0; i < 3; i++) din >> g.color[i];
    for(int i = 0; i < 4; i++) din >> g.coEfficients[i];
    din >> g.shine;

    return din;
}

#endif