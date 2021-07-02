#ifndef OBJECT
#define OBJECT

#include <bits/stdc++.h>
#include "1605002_Vector3D.hpp"
#include "1605002_Ray.hpp"

using namespace std;

class Object
{
protected:

public:
    double color[3];
    double coEfficients[4];
    int shine;

    virtual void draw() = 0;

    virtual double getChed(Ray ray)
    {
        return -1;
    }

    virtual Vector3D getColorAt(Vector3D point)
    {
        return Vector3D(color[0], color[1], color[2]);
    }

    virtual Ray getNormal(Vector3D point)
    {

    }

    double intersect(Ray ray, double* color, int level)
    {
        //cout << ray << endl;
        double t = getChed(ray);
        if(t < 0) return -1;

        if(level == 0) return t;

        Vector3D intersectionPoint = Vector3D(ray.start+t*ray.dir);
        Vector3D chedCol = getColorAt(intersectionPoint);
        for(int i = 0; i < 3; i++) color[i] = chedCol.coords[i]*coEfficients[0];
        Ray normal = getNormal(intersectionPoint);

        return t;
    }

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