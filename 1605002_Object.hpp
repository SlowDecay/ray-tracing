#ifndef OBJECT
#define OBJECT

#include <bits/stdc++.h>

#include "1605002_Vector3D.hpp"
#include "1605002_Ray.hpp"
#include "1605002_Light.hpp"
#include "1605002_Constants.hpp"

using namespace std;

class Object
{
protected:
public:
    Object()
    {
        objects.push_back(this);
    }

    static vector<Object *> objects;

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
        return Vector3D(this->color[0], this->color[1], this->color[2]);
    }

    virtual Ray getNormal(Vector3D point)
    {
    }

    double intersect(Ray ray, double *col, int level, int maxLevel)
    {
        double t = getChed(ray);
        if (t < 0)
            return -1;

        if (level == 0)
            return t;

        Vector3D intersectionPoint = Vector3D(ray.start + t * ray.dir);
        Vector3D chedCol = getColorAt(intersectionPoint);
        for (int i = 0; i < 3; i++)
            col[i] += chedCol.coords[i] * coEfficients[0];
        Ray normal = getNormal(intersectionPoint);

        for (Light *l : Light::lights)
        {
            bool shaded = false;
            Ray incident = Ray(l->lightPos, intersectionPoint - (l->lightPos));
            Ray reflected = Ray(intersectionPoint, incident.dir - 2 * incident.dir.dot(normal.dir) * normal.dir);
            
            double selft = (intersectionPoint - (l->lightPos)).getLength();

            if (selft < EPS)
                continue;

            for (Object *o : Object::objects)
            {
                double ot = o->intersect(incident, col, 0, maxLevel);
                if (ot > 0 && ot+EPS < selft)
                {
                    shaded = true;
                    break;
                }
            }

            if (!shaded)
            {
                double phongValue = max(0.0, (-ray.dir).dot(reflected.dir));

                for (int i = 0; i < 3; i++)
                {
                    col[i] += l->color[i] * coEfficients[1] * max(0.0, (-incident.dir).dot(normal.dir)) * chedCol.coords[i];
                    col[i] += l->color[i] * coEfficients[2] * pow(phongValue, shine) * chedCol.coords[i];
                }
            }
        }

        if(level < maxLevel)
        {
            Ray reflected = Ray(intersectionPoint, ray.dir - 2 * ray.dir.dot(normal.dir) * normal.dir);
            reflected.start += reflected.dir*EPS*1000;

            int nearest = -1;
            double tmin = INF;

            for(int k = 0; k < Object::objects.size(); k++)
            {
                Object* o = objects[k];

                double tn = o->intersect(reflected, col, 0, maxLevel);
                if(tn > 0 && tn < tmin) tmin = tn, nearest = k;
            }

            if(nearest != -1)
            {
                double *colRef = new double[3];
                for(int i = 0; i < 3; i++) colRef[i] = 0;

                double tn = objects[nearest]->intersect(reflected, colRef, level+1, maxLevel);
                for(int i = 0; i < 3; i++) col[i] += colRef[i]*coEfficients[3];

                delete[] colRef;
            }
        }

        return t;
    }

    void setColor(double color[])
    {
        for (int i = 0; i < 3; i++)
            this->color[i] = color[i];
    }
    void setCoEfficients(double coEfficients[])
    {
        for (int i = 0; i < 3; i++)
            this->coEfficients[i] = coEfficients[i];
    }
    void setShine(int shine) { this->shine = shine; }
};

vector<Object *> Object::objects = vector<Object *>();

#endif