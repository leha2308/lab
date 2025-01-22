#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#define SUCCESS 0
#define INVALID_PARAMETER 1
#define NOT_ENOUGH_POINTS 2

typedef struct {
    double x, y;
} Point;

 double cross_product(double ax, double ay, double bx, double by) {
    return ax * by - ay * bx;
}

int is_polygon_convex(int count, ...) {
    if (count < 3) {

        return NOT_ENOUGH_POINTS;
    }

    va_list args;
    va_start(args, count);

    Point points[count];
    for (int i = 0; i < count; ++i) {
        points[i].x = va_arg(args, double);
        points[i].y = va_arg(args, double);
    }

    va_end(args);

    int has_positive = 0, has_negative = 0;

    for (int i = 0; i < count; ++i) {

        Point a = points[i];
        Point b = points[(i + 1) % count];
        Point c = points[(i + 2) % count];

        double abx = b.x - a.x;
        double aby = b.y - a.y;
        double bcx = c.x - b.x;
        double bcy = c.y - b.y;

        double cross = cross_product(abx, aby, bcx, bcy);
        if (cross > 0) {
            has_positive = 1;
        } else if (cross < 0) {
            has_negative = 1;
        }

        if (has_positive && has_negative) {
            return INVALID_PARAMETER;
        }
    }

    return SUCCESS;
}

int main() {

    int result = is_polygon_convex(4,
                                   1.0, 0.0,
                                   4.0, 0.0,
                                   4.0, 3.0,
                                   6.0, 3.0);
    if (result == SUCCESS) {
        printf("First example: The polygon is convex.\n");
    } else {
        printf("First example: The polygon is not convex or there is an error.\n");
    }

    result = is_polygon_convex(5,
                               6.0, 0.0,
                               4.0, 0.0,
                               2.0, 2.0,
                               3.0, 4.0,
                               4.0, 4.0);
    if (result == SUCCESS) {
        printf("Second example: The polygon is convex.\n");
    } else {
        printf("Second example: The polygon is not convex or there is an error.\n");
    }

    return 0;
}
