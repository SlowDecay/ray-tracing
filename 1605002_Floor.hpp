#ifndef FLOOR
#define FLOOR

#include <bits/stdc++.h>
#include <GL/glut.h>
#include <windows.h>

#include "1605002_Object.hpp"
#include "1605002_Vector3D.hpp"
#include "1605002_Constants.hpp"
#include "1605002_Bitmap_Image.hpp"

using namespace std;

Vector3D floorPoints[FLOOR_POINTS + 5][FLOOR_POINTS + 5];

struct Floor : public Object
{
private:
public:
    Vector3D bottomLeft;
    double floorWidth, tileWidth;
    bitmap_image image;

    Floor(double floorWidth, double tileWidth) : image("1605002_biis.bmp")
    {
        bottomLeft = Vector3D(-floorWidth / 2, -floorWidth / 2, 0);
        this->floorWidth = floorWidth, this->tileWidth = tileWidth;

        createPoints();
    }

    void createPoints()
    {
        int n = round(floorWidth / tileWidth);

        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                floorPoints[i][j] = bottomLeft + Vector3D(i * tileWidth, j * tileWidth, 0);
            }
        }
    }

    virtual string getType()
    {
        return "floor";
    }

    virtual void draw()
    {
        int n = round(floorWidth / tileWidth);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                glBegin(GL_QUADS);
                {
                    if ((i + j) % 2 == 0)
                        glColor3f(0, 0, 0);
                    else
                        glColor3f(255, 255, 255);

                    glVertex3f(floorPoints[i][j].x(), floorPoints[i][j].y(), floorPoints[i][j].z());
                    glVertex3f(floorPoints[i][j + 1].x(), floorPoints[i][j + 1].y(), floorPoints[i][j + 1].z());
                    glVertex3f(floorPoints[i + 1][j + 1].x(), floorPoints[i + 1][j + 1].y(), floorPoints[i + 1][j + 1].z());
                    glVertex3f(floorPoints[i + 1][j].x(), floorPoints[i + 1][j].y(), floorPoints[i + 1][j].z());
                }
                glEnd();
            }
        }
    }

    virtual double getChed(Ray ray)
    {
        if (fabs(ray.start.z()) < EPS)
            return -1;
        if (fabs(ray.dir.z()) < EPS)
            return -1;

        double t = -ray.start.z() / ray.dir.z();

        if (t <= 0)
            return -1;

        Vector3D ched = ray.start + t * ray.dir;
        if (fabs(ched.x()) > floorWidth / 2 || fabs(ched.y()) > floorWidth / 2)
            return -1;

        return t;
    }

    virtual Vector3D getColorAt(Vector3D point)
    {
        int i = (point.x() - bottomLeft.x()) / tileWidth;
        int j = (point.y() - bottomLeft.y()) / tileWidth;

        if ((i + j) % 2 == 0)
        {
            double tilex = bottomLeft.x() + i * tileWidth;
            double tiley = bottomLeft.y() + j * tileWidth;

            int imageWidth = image.width();
            int imageHeight = image.height();

            int pixelx = round((point.x() - tilex) / tileWidth * imageWidth);
            int pixely = round((point.y() - tiley) / tileWidth * imageHeight);

            if (pixelx < 1)
                pixelx = 1;
            if (pixelx > imageWidth)
                pixelx = imageWidth;

            if (pixely < 1)
                pixely = 1;
            if (pixely > imageHeight)
                pixely = imageHeight;

            unsigned char r, g, b;
            image.get_pixel(pixelx, pixely, r, g, b);

            Vector3D col(r / 255.0, g / 255.0, b / 255.0);
            return col * TEX_COEFF;
        }
        else
            return Vector3D(1, 1, 1);
    }

    virtual Ray getNormal(Vector3D point, Ray incident)
    {
        if (incident.start.z() > 0)
            return Ray(point, Vector3D(0, 0, 1));
        else
            return Ray(point, Vector3D(0, 0, -1));
    }

    virtual void chapao()
    {
        cout << "floor" << endl;
        cout << "floorwidth = " << floorWidth << endl;
        cout << "radius = " << tileWidth << endl;
        cout << "colors = " << color[0] << " " << color[1] << " " << color[2] << endl;
        cout << "coEffs = " << coEfficients[0] << " " << coEfficients[1] << " " << coEfficients[2] << " " << coEfficients[3] << endl;
        cout << "shine = " << shine << endl
             << endl;
    }
};

#endif