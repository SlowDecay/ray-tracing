#ifndef LIGHT
#define LIGHT

#include "1605002_Vector3D.hpp"

class Light
{
public:
    Vector3D lightPos;
    double color[3];

    static vector<Light *> lights;

    Light() { lights.push_back(this); }
    Light(Vector3D lightPos, double color[])
    {
        this->lightPos = lightPos;
        for (int i = 0; i < 3; i++)
            this->color[i] = color[i];

        lights.push_back(this);
    }

    void draw()
    {
        glPointSize(5);
        glBegin(GL_POINTS);
        glColor3f(color[0], color[1], color[2]);
        glVertex3f(lightPos.x(), lightPos.y(), lightPos.z());
        glEnd();
        glPointSize(1);
    }
};

ostream &operator<<(ostream &dout, const Light &l)
{
    dout << l.lightPos << ", (" << l.color[0] << ", " << l.color[1] << ", " << l.color[2] << ")";
    return dout;
}

istream &operator>>(istream &din, Light &l)
{
    din >> l.lightPos;
    for (int i = 0; i < 3; i++)
        din >> l.color[i];

    return din;
}

vector<Light *> Light::lights = vector<Light *>();

#endif