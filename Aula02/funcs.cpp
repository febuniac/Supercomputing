#include <math.h>

double inner_prod(double *a, double *b, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i] * b[i];
    }
    return sqrt(sum);
}

double sum_positive(double *a, int n) {
    double s = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            s += a[i];
        }
    }
    return s;
}

void sqrt_element(double *a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = sqrt(a[i]);
    }
}

void exp_element(double *a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = exp(a[i]);
    }
}

void log_element(double *a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = log(a[i]);
    }
}

void gauss(double *a, double *b, int n) {
    double p = 1 / sqrt(2.0 * M_PI);
    for (int i = 0; i < n; i++) {
        b[i] = p * exp(-a[i]*a[i]/2);
    }
}
