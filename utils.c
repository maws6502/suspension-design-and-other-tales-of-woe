#include "suspsolv.h"

#include <stdio.h>
#include <math.h>

Point
sub(Point p1, Point p2)
{
    Point q;
    q.x = p1.x - p2.x;
    q.y = p1.y - p2.y;
    q.z = p1.z - p2.z;
    return q;
}

Point
cross(Point p1, Point p2)
{
    Point q;
    q.x = p1.y * p2.z - p2.y * p1.z;
    q.y = p1.z * p2.x - p2.z * p1.x;
    q.z = p1.x * p2.y - p2.x * p1.y;
    return q;
}

Point
add(Point p1, Point p2)
{
    Point q;
    q.x = p1.x + p2.x;
    q.y = p1.y + p2.y;
    q.z = p1.z + p2.z;
    return q;
}

Point
scale(Point p1, double d)
{
    p1.x *= d;
    p1.y *= d;
    p1.z *= d;
    return p1;
}

double
norm(Point p1, Point p2)
{
    Point q = sub(p1, p2);
    return sqrt(q.x*q.x + q.y*q.y + q.z*q.z);
}

Point
normalize(Point p) {
    Point o = {0.0, 0.0, 0.0};
    double n = norm(p, o);
    p.x /=n;
    p.y /=n;
    p.z /=n;
    return p;
}


/* http://paulbourke.net/geometry/rotate/source.c */
Point
rotate_point(Point p1, Point p2, Point p, double theta)
{

    theta *= (M_PI/180);
    Point q = {0.0,0.0,0.0};
    double costheta, sintheta;
    Point r;

    r.x = p2.x - p1.x;
    r.y = p2.y - p1.y;
    r.z = p2.z - p1.z;
    p.x -= p1.x;
    p.y -= p1.y;
    p.z -= p1.z;
    r = normalize(r);

    costheta = cos(theta);
    sintheta = sin(theta);

    q.x += (costheta + (1 - costheta) * r.x * r.x) * p.x;
    q.x += ((1 - costheta) * r.x * r.y - r.z * sintheta) * p.y;
    q.x += ((1 - costheta) * r.x * r.z + r.y * sintheta) * p.z;

    q.y += ((1 - costheta) * r.x * r.y + r.z * sintheta) * p.x;
    q.y += (costheta + (1 - costheta) * r.y * r.y) * p.y;
    q.y += ((1 - costheta) * r.y * r.z - r.x * sintheta) * p.z;

    q.z += ((1 - costheta) * r.x * r.z - r.y * sintheta) * p.x;
    q.z += ((1 - costheta) * r.y * r.z + r.x * sintheta) * p.y;
    q.z += (costheta + (1 - costheta) * r.z * r.z) * p.z;

    q.x += p1.x;
    q.y += p1.y;
    q.z += p1.z;
    return q;
}

/* for lazy debugging */
void
pprint(Point p, char *name) 
{
    printf("%s: %lf %lf %lf\n", name, p.x, p.y, p.z);
}