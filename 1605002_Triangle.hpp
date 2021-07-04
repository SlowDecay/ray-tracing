#ifndef TRIANGLE
#define TRIANGLE

class Triangle;

#include <bits/stdc++.h>
#include <GL/glut.h>
#include <windows.h>

#include "1605002_Object.hpp"
#include "1605002_Vector3D.hpp"
#include "1605002_Matrix.hpp"

using namespace std;

struct Triangle : public Object
{
public:
    Vector3D corners[3];

    Triangle() {}
    Triangle(Vector3D corners[])
    {
        for (int i = 0; i < 3; i++)
            this->corners[i] = corners[i];
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

    virtual double getChed(Ray ray)
    {
        Matrix base;
        for (int i = 0; i < 3; i++)
            base.elements[i][0] = corners[0].coords[i] - corners[1].coords[i];
        for (int i = 0; i < 3; i++)
            base.elements[i][1] = corners[0].coords[i] - corners[2].coords[i];
        for (int i = 0; i < 3; i++)
            base.elements[i][2] = ray.dir.coords[i];

        Matrix betaMat = base;
        for (int i = 0; i < 3; i++)
            betaMat.elements[i][0] = corners[0].coords[i] - ray.start.coords[i];

        Matrix gammaMat = base;
        for (int i = 0; i < 3; i++)
            gammaMat.elements[i][1] = corners[0].coords[i] - ray.start.coords[i];

        Matrix tMat = base;
        for (int i = 0; i < 3; i++)
            tMat.elements[i][2] = corners[0].coords[i] - ray.start.coords[i];

        double hor = base.det();
        if (fabs(hor) < EPS)
            return -1;

        double beta = betaMat.det() / hor;
        double gamma = gammaMat.det() / hor;
        double t = tMat.det() / hor;

        if (beta < 0 || gamma < 0 || beta + gamma > 1)
            return -1;
        if (t < 0)
            return -1;
        return t;
    }

    virtual Ray getNormal(Vector3D point, Ray incident)
    {
        Vector3D dir = (corners[1] - corners[0]).cross(corners[2] - corners[0]);

        if ((-incident.dir).dot(dir) >= 0)
            return Ray(point, dir);
        else
            return Ray(point, -dir);
    }

    virtual void chapao()
    {
        cout << "triangle" << endl;
        for (int i = 0; i < 3; i++)
            cout << "corners[" << i << "] = " << corners[i] << endl;
        cout << "colors = " << color[0] << " " << color[1] << " " << color[2] << endl;
        cout << "coEffs = " << coEfficients[0] << " " << coEfficients[1] << " " << coEfficients[2] << " " << coEfficients[3] << endl;
        cout << "shine = " << shine << endl
             << endl;
    }

    friend istream &operator>>(istream &, Triangle &);
};

istream &operator>>(istream &din, Triangle &t)
{
    for (int i = 0; i < 3; i++)
        din >> t.corners[i];
    for (int i = 0; i < 3; i++)
        din >> t.color[i];
    for (int i = 0; i < 4; i++)
        din >> t.coEfficients[i];
    din >> t.shine;

    return din;
}

#endif