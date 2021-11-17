#include <stdio.h>
#include "suspsolv.h"

int
main(int argc, char *argv[])
{
    Point upper_control_point_1 = {-1119.00, 212.00, 179.00};
    Point upper_control_point_2 = {-869.00, 212.00, 179.00};
    Point lower_control_point_1 = {-1114.00, 215.00, 16.50};
    Point lower_control_point_2 = {-864.00, 215.00, 3.40};

    Point upper_outboard = {-986.00,    632.00  ,   45.00};
    Point lower_outboard = {-1000.00,    637.00,   -110.00};

    Point tie_rod_inner = {-885.00 ,   195.00,     80.00};
    Point tie_rod_outer = {-900.00  ,  620.00 ,   -42.00};

    double droop_angle = -10.9;
    double bump_angle = 23.4;

    double wct = worst_case_toe(upper_control_point_1, upper_control_point_2, upper_outboard, lower_control_point_1, lower_control_point_2, lower_outboard, tie_rod_inner, tie_rod_outer, bump_angle, droop_angle);

    printf("%lf\n", wct);

    return 0;
}