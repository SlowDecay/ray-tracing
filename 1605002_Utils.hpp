#ifndef UTILS
#define UTILS

#include <bits/stdc++.h>
using namespace std;

double getSol(double a, double b, double c, double &t1, double &t2)
{
    double d2 = b*b-4*a*c;
    if(d2 < 0) return -1;

    double d = sqrt(d2);
    t1 = (-b-d)/(2*a);
    t2 = (-b+d)/(2*a);

    if(t1 > 0) return t1;
    if(t2 > 0) return t2;

    return -1;
}

#endif