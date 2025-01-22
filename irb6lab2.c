#include <stdio.h>
#include <stdarg.h>


int evaluate_polynomial(double x, int n, double *result, ...) {
    if (n < 0 || !result) {
        return -1;
    }

    va_list args;
    va_start(args, result);

    *result = 0.0;
    double power = 1.0;

    for (int i = 0; i <= n; ++i) {
        double coefficient = va_arg(args, double);
        *result += coefficient * power;
        power *= x;
    }

    va_end(args);
    return 0;
}

int main() {
    double x = 3.0;
    int n = 2;
    double result;

    int status = evaluate_polynomial(x, n, &result, 2.0, 5.0, 5.0);

    if (status == 0) {
        printf("The value of the polynomial at \n x = %.2f, n = %d is %.2f\n", x, n, result);
    } else {
        printf("An error occurred while evaluating the polynomial.\n");
    }

    return 0;
}




