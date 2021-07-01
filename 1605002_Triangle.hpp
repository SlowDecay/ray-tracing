#ifndef TRIANGLE
#define TRIANGLE

#include <bits/stdc++.h>
#include <GL/glut.h>
#include <windows.h>

#include "1605002_Object.hpp"

using namespace std;

struct Triangle : public Object
{
private:
    Vector3D corners[3];

public:
    Triangle() {}
    Triangle(Vector3D corners[])
    {
        for(int i = 0; i < 3; i++) this->corners[i] = corners[i];
    }

    virtual void draw()
    {
        glColor3f(color[0], color[1], color[2]);
        glBegin(GL_TRIANGLES);
        {
            glVertex3f(corners[0].x(), corners[0].y(), corners[0].z());
            glVertex3f(corners[1].x(), corners[1].y(), corners[1].z());
            glVertex3f(corners[2].x(), corners[2].y(), corners[2].z());
        }
        glEnd();
    }
};

#endif