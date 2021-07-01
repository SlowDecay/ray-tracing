#ifndef SPHERE
#define SPHERE

#include <bits/stdc++.h>
#include <GL/glut.h>
#include <windows.h>

#include "1605002_Object.hpp"
#include "1605002_Constants.hpp"

using namespace std;

Vector3D spherePoints[SPHERE_STACKS + 10][SPHERE_SLICES + 10];

class Sphere : public Object
{
private:
    Vector3D center;
    double radius;

    void drawRing()
    {
        //draw quads using generated points
        for (int i = 0; i < SPHERE_STACKS; i++)
        {
            for (int j = 0; j < SPHERE_SLICES; j++)
            {
                glBegin(GL_QUADS);
                {
                    glVertex3f(spherePoints[i][j].x(), spherePoints[i][j].y(), spherePoints[i][j].z());
                    glVertex3f(spherePoints[i][j + 1].x(), spherePoints[i][j + 1].y(), spherePoints[i][j + 1].z());
                    glVertex3f(spherePoints[i + 1][j + 1].x(), spherePoints[i + 1][j + 1].y(), spherePoints[i + 1][j + 1].z());
                    glVertex3f(spherePoints[i + 1][j].x(), spherePoints[i + 1][j].y(), spherePoints[i + 1][j].z());
                }
                glEnd();
            }
        }
    }

    void drawHalfSphere(int shamne)
    {
        //generate points
        for (int i = 0; i <= SPHERE_STACKS; i++)
        {
            double h = radius * sin(((double)i / (double)SPHERE_STACKS) * (PI / 2));
            double r = radius * cos(((double)i / (double)SPHERE_STACKS) * (PI / 2));
            for (int j = 0; j <= SPHERE_SLICES; j++)
            {
                double x = r * cos(((double)j / (double)SPHERE_SLICES) * 2 * PI);
                double y = h * shamne;
                double z = r * sin(((double)j / (double)SPHERE_SLICES) * 2 * PI);

                spherePoints[i][j] = Vector3D(x, y, z);
            }
        }

        drawRing();
    }

public:
    Sphere() {}
    Sphere(Vector3D center, double radius) : center(center), radius(radius) {}

    virtual void draw()
    {
        glPushMatrix();
        glTranslatef(center.coords[0], center.coords[1], center.coords[2]);
        glColor3f(color[0], color[1], color[2]);
        drawHalfSphere(1);
        drawHalfSphere(-1);
        glPopMatrix();
    }
};

#endif