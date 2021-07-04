#ifndef GENERAL
#define GENERAL

#include <bits/stdc++.h>
#include <GL/glut.h>
#include <windows.h>

#include "1605002_Object.hpp"
#include "1605002_Vector3D.hpp"
#include "1605002_Utils.hpp"

using namespace std;

struct General : public Object
{
public:
    double a, b, c, d, e, f, g, h, i, j;
    Vector3D refPoint;
    double length, width, height;

    General() {}

    virtual string getType()
    {
        return "general";
    }

    virtual void draw()
    {
        return;
    }

    virtual double getChed(Ray ray)
    {
        double x0 = ray.start.x(), y0 = ray.start.y(), z0 = ray.start.z();
        double x1 = ray.dir.x(), y1 = ray.dir.y(), z1 = ray.dir.z();

        double c0 = a*x1*x1 + b*y1*y1 + c*z1*z1 + d*x1*y1 + e*x1*z1 + f*y1*z1;
        double c1 = 2*a*x0*x1 + 2*b*y0*y1 + 2*c*z0*z1 + d*(x0*y1 + x1*y0) + e*(x0*z1 + x1*z0);
        c1 += f*(y0*z1 + y1*z0) + g*x1 + h*y1 + i*z1;
        double c2 = a*x0*x0 + b*y0*y0 + c*z0*z0 + d*x0*y0 + e*x0*z0 + f*y0*z0 + g*x0 + h*y0 + i*z0 + j;

        double t1, t2;
        double t = getSol(c0, c1, c2, t1, t2);

        if(t < 0) return -1;

        //cout << t1 << " " << t2 << endl;

        if(t1 > 0)
        {
            //cout << "t1 paise :'(" << endl;
            Vector3D kache = ray.start+t1*ray.dir;
            if(isVitore(kache)) return t1;
        }
        
        if(t2 > 0)
        {
            //cout << "t2 paise :'(" << endl;
            Vector3D dure = ray.start+t2*ray.dir;
            if(isVitore(dure)) return t2;
        }

        return -1;
    }

    bool isVitore(Vector3D point)
    {
        double lns[] = {length, width, height};
        for(int idx = 0; idx < 3; idx++)
        {
            if(fabs(lns[idx]) < EPS) continue;
            if(point.coords[idx] < refPoint.coords[idx]) return false;
            if(point.coords[idx] > refPoint.coords[idx]+lns[idx]) return false;
        }

        return true;
    }

    virtual void chapao()
    {
        cout << "general" << endl;
        cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << " " << g << " " << h << " " << i << " " << j << endl;
        cout << "refPoint = " << refPoint << endl;
        cout << "length = " << length << ", width = " << width << ", height" << height << endl;
        cout << "colors = " << color[0] << " " << color[1] << " " << color[2] << endl;
        cout << "coEffs = " << coEfficients[0] << " " << coEfficients[1] << " " << coEfficients[2] << " " << coEfficients[3] << endl;
        cout << "shine = " << shine << endl << endl;
    }

    virtual Ray getNormal(Vector3D point, Ray incident)
    {
        double x = point.x(), y = point.y(), z = point.z();
        Vector3D dir(2*a*x + d*y + e*z + g, 2*b*y + d*x + f*z + h, 2*c*z + e*x + f*y + i);

        return Ray(point, dir);
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