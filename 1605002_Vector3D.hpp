#ifndef VECTOR3D
#define VECTOR3D

class Vector3D;

#include <bits/stdc++.h>
#include "1605002_Constants.hpp"

using namespace std;

class Vector3D
{
public:
    double coords[3];

    Vector3D()
    {
        for (int i = 0; i < 3; i++)
            coords[i] = 0;
    }
    Vector3D(double x, double y, double z)
    {
        coords[0] = x, coords[1] = y, coords[2] = z;
    }

    double x() const { return coords[0]; }
    double y() const { return coords[1]; }
    double z() const { return coords[2]; }

    Vector3D operator+(const Vector3D &rhs) const
    {
        double tmp[3];
        for (int i = 0; i < 3; i++)
            tmp[i] = coords[i] + rhs.coords[i];

        return Vector3D(tmp[0], tmp[1], tmp[2]);
    }
    Vector3D operator-(const Vector3D &rhs) const
    {
        double tmp[3];
        for (int i = 0; i < 3; i++)
            tmp[i] = coords[i] - rhs.coords[i];

        return Vector3D(tmp[0], tmp[1], tmp[2]);
    }

    Vector3D operator-() const
    {
        double tmp[3];
        for (int i = 0; i < 3; i++)
            tmp[i] = -coords[i];

        return Vector3D(tmp[0], tmp[1], tmp[2]);
    }

    Vector3D operator+=(const Vector3D &rhs)
    {
        for (int i = 0; i < 3; i++)
            coords[i] += rhs.coords[i];
        return *this;
    }

    Vector3D operator-=(const Vector3D &rhs)
    {
        for (int i = 0; i < 3; i++)
            coords[i] -= rhs.coords[i];
        return *this;
    }

    Vector3D operator*(double d) const
    {
        double tmp[3];
        for (int i = 0; i < 3; i++)
            tmp[i] = coords[i] * d;

        return Vector3D(tmp[0], tmp[1], tmp[2]);
    }

    Vector3D operator/(double d) const
    {
        if(fabs(d) < EPS) return Vector3D(INF, INF, INF);

        double tmp[3];
        for (int i = 0; i < 3; i++)
            tmp[i] = coords[i] / d;

        return Vector3D(tmp[0], tmp[1], tmp[2]);
    }

    double dot(const Vector3D &rhs) const
    {
        double ans = 0;
        for (int i = 0; i < 3; i++)
            ans += coords[i] * rhs.coords[i];

        return ans;
    }

    Vector3D cross(const Vector3D &rhs) const
    {
        double tmp[3];

        tmp[0] = coords[1] * rhs.coords[2] - coords[2] * rhs.coords[1];
        tmp[1] = coords[2] * rhs.coords[0] - coords[0] * rhs.coords[2];
        tmp[2] = coords[0] * rhs.coords[1] - coords[1] * rhs.coords[0];

        return Vector3D(tmp[0], tmp[1], tmp[2]);
    }

    double getLength() const
    {
        return sqrt(this->dot(*this));
    }

    Vector3D &normalize()
    {
        double d = 0;
        for (int i = 0; i < 3; i++)
            d += coords[i] * coords[i];

        if (fabs(d) > EPS)
        {
            d = sqrt(d);
            for (int i = 0; i < 3; i++)
                coords[i] /= d;
        }

        return *this;
    }

    friend Vector3D operator*(double, const Vector3D &);
    friend ostream &operator<<(ostream &, const Vector3D &);
    friend istream &operator>>(istream &, Vector3D &);
};

Vector3D operator*(double d, const Vector3D &rhs)
{
    double tmp[3];
    for (int i = 0; i < 3; i++)
        tmp[i] = d * rhs.coords[i];

    return Vector3D(tmp[0], tmp[1], tmp[2]);
}

ostream &operator<<(ostream &dout, const Vector3D &rhs)
{
    dout << "(" << rhs.coords[0] << ", " << rhs.coords[1] << ", " << rhs.coords[2] << ")";
    return dout;
}

istream &operator>>(istream &din, Vector3D &rhs)
{
    din >> rhs.coords[0] >> rhs.coords[1] >> rhs.coords[2];
    return din;
}

#endif