#ifndef LIGHT
#define LIGHT

class Light
{
public:
    Vector3D lightPos;
    double color[3];

    Light() {}
    Light(Vector3D lightPos, double color[])
    {
        this->lightPos = lightPos;
        for(int i = 0; i < 3; i++) this->color[i] = color[i];
    }

    void draw()
    {
        Sphere s(lightPos, 1);
        s.setColor(color);
        s.draw();
    }
};

istream& operator>>(istream& din, Light& l)
{
    din >> l.lightPos;
    for(int i = 0; i < 3; i++) din >> l.color[i];

    return din;
}

#endif