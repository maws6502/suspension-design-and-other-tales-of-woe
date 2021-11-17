struct point {
    double x;
    double y;
    double z;
};
typedef struct point Point;

struct outboard {
    Point tro;
    Point uco;
    Point lco;
};
typedef struct outboard Outboard;

#ifndef M_PI
#define M_PI    3.141592653589793238462643383279502884 /* pi */
#endif

#define N_PTS 10000
#define DEGREES_PER_STEP 1

Point       rotate_point        (Point, Point, Point, double);

Point       sub                 (Point, Point);
Point       add                 (Point, Point);
Point       cross               (Point, Point);

Point       scale               (Point, double);

double      norm                (Point, Point);

Point       normalize           (Point);

void        pprintf             (Point, char *);

Outboard    actuate_suspension  (Point, Point, Point, Point, Point, Point, Point, Point, double);

double      worst_case_toe      (Point, Point, Point, Point, Point, Point, Point, Point, double, double);