#ifndef FLOOR
#define FLOOR

#include <bits/stdc++.h>
#include <GL/glut.h>
#include <windows.h>

#include "1605002_Object.hpp"
#include "1605002_Vector3D.hpp"
#include "1605002_Constants.hpp"

using namespace std;

Vector3D floorPoints[FLOOR_POINTS+5][FLOOR_POINTS+5];

struct Floor : public Object
{
private:
    Vector3D bottomLeft;
    double floorWidth, tileWidth;

public:
    Floor(double floorWidth, double tileWidth)
    {
        bottomLeft = Vector3D(-floorWidth / 2, -floorWidth / 2, 0);
        this->floorWidth = floorWidth, this->tileWidth = tileWidth;

        createPoints();
    }

    void createPoints()
    {
        int n = round(floorWidth/tileWidth);

        for(int i = 0; i <= n; i++)
        {
            for(int j = 0; j <= n; j++)
            {
                floorPoints[i][j] = bottomLeft+Vector3D(i*tileWidth, j*tileWidth, 0);
            }
        }
    }

    virtual void draw()
    {
        int n = round(floorWidth/tileWidth);

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                glBegin(GL_QUADS);
                {
                    if((i+j)%2) glColor3f(0, 0, 0);
                    else glColor3f(255, 255, 255);

                    glVertex3f(floorPoints[i][j].x(), floorPoints[i][j].y(), floorPoints[i][j].z());
                    glVertex3f(floorPoints[i][j + 1].x(), floorPoints[i][j + 1].y(), floorPoints[i][j + 1].z());
                    glVertex3f(floorPoints[i + 1][j + 1].x(), floorPoints[i + 1][j + 1].y(), floorPoints[i + 1][j + 1].z());
                    glVertex3f(floorPoints[i + 1][j].x(), floorPoints[i + 1][j].y(), floorPoints[i + 1][j].z());
                }
                glEnd();
            }
        }
    }
};

#endif