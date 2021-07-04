#ifndef MATRIX
#define MATRIX

#include <bits/stdc++.h>

using namespace std;

class Matrix
{
public:
    double elements[3][3];

    double det()
    {
        double x = elements[0][0] * (elements[1][1] * elements[2][2] - elements[1][2] * elements[2][1]);
        double y = elements[0][1] * (elements[1][2] * elements[2][0] - elements[1][0] * elements[2][2]);
        double z = elements[0][2] * (elements[1][0] * elements[2][1] - elements[1][1] * elements[2][0]);

        return x + y + z;
    }
};

#endif