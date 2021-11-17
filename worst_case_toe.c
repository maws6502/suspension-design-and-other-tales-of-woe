#include <math.h>

#include "suspsolv.h"

double
worst_case_toe(Point ucp_1, Point ucp_2, Point uco, Point lcp_1, Point lcp_2, Point lco, Point tri, Point tro, double bump_angle, double droop_angle)
{
    double static_m, toe, toe_m, toe2;
    Outboard o;
    static_m = (tro.y - uco.y)/(tro.x - uco.x);

    o = actuate_suspension(ucp_1, ucp_2, uco, lcp_1, lcp_2, lco, tri, tro, bump_angle);
    toe_m = (o.tro.y - o.uco.y)/(o.tro.x - o.uco.x);

    toe = fabs(atan((toe_m - static_m)/(1 - toe_m * static_m)));
    o = actuate_suspension(ucp_1, ucp_2, uco, lcp_1, lcp_2, lco, tri, tro, droop_angle);

    toe_m = (o.tro.y - o.uco.y)/(o.tro.x - o.uco.x);

    toe2 = fabs(atan((toe_m - static_m)/(1 - toe_m * static_m)));

    if (toe2 > toe) toe = toe2;
    
    return toe * 180.0 / M_PI;
}