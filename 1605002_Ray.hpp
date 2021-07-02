#ifndef RAY
#define RAY

#include <bits/stdc++.h>
#include <GL/glut.h>
#include <windows.h>

#include "1605002_Object.hpp"
#include "1605002_Vector3D.hpp"
#include "1605002_Globals.hpp"

using namespace std;

class Ray : public Object
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

#endif