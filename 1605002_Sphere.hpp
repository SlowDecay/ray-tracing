#ifndef SPHERE
#define SPHERE

#include <bits/stdc++.h>
#include <GL/glut.h>
#include <windows.h>

#include "1605002_Object.hpp"
#include "1605002_Vector3D.hpp"
#include "1605002_Constants.hpp"
#include "1605002_Utils.hpp"

using namespace std;

Vector3D spherePoints[SPHERE_STACKS + 10][SPHERE_SLICES + 10];

class Sphere : public Object
{
public:
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

    virtual double getChed(Ray ray)
    {
        ray.start -= center;

        double a = 1;
        double b = 2 * ray.start.dot(ray.dir);
        double c = ray.start.dot(ray.start) - radius * radius;

        double t1, t2;
        return getSol(a, b, c, t1, t2);
    }

    virtual Ray getNormal(Vector3D point, Ray incident)
    {
        return Ray(point, point - center);
    }

    virtual void chapao()
    {
        cout << "sphere" << endl;
        cout << "center = " << center << endl;
        cout << "radius = " << radius << endl;
        cout << "colors = " << color[0] << " " << color[1] << " " << color[2] << endl;
        cout << "coEffs = " << coEfficients[0] << " " << coEfficients[1] << " " << coEfficients[2] << " " << coEfficients[3] << endl;
        cout << "shine = " << shine << endl
             << endl;
    }

    friend istream &operator>>(istream &, Sphere &);
};

istream &operator>>(istream &din, Sphere &s)
{
    din >> s.center >> s.radius;
    for (int i = 0; i < 3; i++)
        din >> s.color[i];
    for (int i = 0; i < 4; i++)
        din >> s.coEfficients[i];
    din >> s.shine;

    return din;
}

#endif