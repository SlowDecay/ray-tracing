#ifndef RAY
#define RAY

#include <bits/stdc++.h>
#include <GL/glut.h>
#include <windows.h>

#include "1605002_Vector3D.hpp"

using namespace std;

class Ray
{
public:
    Vector3D start;
    Vector3D dir;

    Ray(Vector3D start, Vector3D dir)
    {
        this->start = start;
        this->dir = dir.normalize();
    }
};

ostream &operator<<(ostream &dout, const Ray &rhs)
{
    dout << "(" << rhs.start << ", " << rhs.dir << ")";
    return dout;
}

#endif