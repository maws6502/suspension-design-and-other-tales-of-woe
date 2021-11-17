#include <float.h>
#include <math.h>

#include "suspsolv.h"

Outboard
actuate_suspension(Point ucp_1, Point ucp_2, Point uco, Point lcp_1, Point lcp_2, Point lco, Point tri, Point tro, double angle)
{
    Outboard out;
    Point lower_circle[N_PTS];
    Point tro_circle[N_PTS];
    Point uco_new, trbase, trstart;
    int i, ci1, ci2;
    double a, b, c, d, s, area, trd, ph;
    double current_angle = 0.0;
    double cd1, cd2, dist;
    double direction;

    direction = fabs(angle)/angle;

    a = norm(tro, uco);
    b = norm(lco, uco);
    c = norm(tro, lco);
    d = norm(tro, tri);

    /* assume a triangle between lco, uco and tro
     * we use some bullshit highschool math to calculate it's area
     * then use that to find the height of the triangle as we have base
     * then we assume another triangle between the foot of the perpendicular
     * of the tro to the uco-lco line, use pythagoras theorem to calculate 
     * the distance from the uco to this perpendicular. then later we can create 
     * the needed tro circle using this information somehow */

    s = (a + b + c)/2.0;
    area = sqrt(s * (s-a) * (s-b) * (s-c));
    trd = 2.0 * area / b;
    ph = sqrt(c * c - trd * trd);


    /* first, generate the entire circle of N_PTS for lower circle */
    for (i = 0; i < N_PTS; i++)
        lower_circle[i] = rotate_point(lcp_1, lcp_2, lco, (double) i * (360.0/N_PTS));

    
    /* now iterate through angles until we hit the required angle, DEGREES_PER_STEP at a time) */
    while (fabs(current_angle) <= fabs(angle)) {
        uco_new = rotate_point(ucp_1, ucp_2, uco, current_angle);
        /* find the 2 closest lower outboard points, choose whichever is closer to the old one */
        cd1 = DBL_MAX;
        cd2 = DBL_MAX;
        ci1 = 0;
        ci2 = 0;
        for (i = 0; i < N_PTS; i++) {
            dist = fabs(norm(lower_circle[i], uco_new) - b);
            if (dist < cd1) {
                cd2 = cd1;
                cd1 = dist;
                ci2 = ci1;
                ci1 = i;
            } else if (dist < cd2) {
                cd2 = dist;
                ci2 = i;
            }
        }
        cd1 = norm(lco, lower_circle[ci1]);
        cd2 = norm(lco, lower_circle[ci2]);
        lco = cd1 > cd2 ? lower_circle[ci2] : lower_circle[ci1];

        /* now we find the tie rod end by first finding the point
         * ph away from the lco on the line joining lco and uco
         * then we can find a perpendicular from that point and 
         * make the tro circle */

        trbase = add(scale(normalize(sub(uco_new, lco)), ph), lco);

        /* assumption here is that the uco-lco line is somehow not 
         * parallel to the ucp_1-ucp_2 line */

        trstart = add(scale(normalize(cross(sub(trbase, lco), sub(ucp_1, ucp_2))), trd), trbase);

        cd1 = DBL_MAX;
        cd2 = DBL_MAX;
        ci1 = 0;
        ci2 = 0;

        for (i = 0; i < N_PTS; i++)
            tro_circle[i] = rotate_point(lco, uco_new, trstart, (double) i * (360.0/N_PTS));

        for (i = 0; i < N_PTS; i++) {
            dist = fabs(norm(tro_circle[i], tri) - d);
            if (dist < cd1) {
                cd2 = cd1;
                cd1 = dist;
                ci2 = ci1;
                ci1 = i;
            } else if (dist < cd2) {
                cd2 = dist;
                ci2 = i;
            }
        }

        cd1 = norm(tro, tro_circle[ci1]);
        cd2 = norm(tro, tro_circle[ci2]);
        tro = cd1 > cd2 ? tro_circle[ci2] : tro_circle[ci1];
        current_angle += DEGREES_PER_STEP * direction;
    }

    out.uco = uco_new;
    out.lco = lco;
    out.tro = tro;

    return out;
}