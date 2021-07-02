#ifndef UTILS
#define UTILS

#include <bits/stdc++.h>
using namespace std;

double getSol(double a, double b, double c)
{

    double d2 = b*b-4*a*c;
    if(d2 < 0) return -1;

    double d = sqrt(d2);
    double t1 = (-b-d)/(2*a);
    double t2 = (-b+d)/(2*a);

    if(t1 > 0) return t1;
    if(t2 > 0) return t2;

    return -1;
}

#endif