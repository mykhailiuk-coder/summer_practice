//Recursion

#include <stdio.h>
#include <math.h>

//Task 1: Calculate Sx = sum(x_i / (1 + |y_i|)), where x_i and y_i are defined recursively.
double getx(int i) {
    if (i == 1) {
        return 1.0;
    }
    else {
        return 0.3 * getx(i - 1);
    }
}

double gety(int i) {
    if (i == 1) {
        return 1.0;
    }
    else {
        double x_prev = getx(i - 1);
        double y_prev = gety(i - 1);
        return x_prev * x_prev + y_prev;
    }
}

double getSx(int n) {
    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        double x_i = getx(i);
        double y_i = gety(i);
        sum += x_i / (1.0 + fabs(y_i));
    }
    return sum;
}

//Task 2: Calculate the nested square root: sqrt(n + sqrt(n-1 + sqrt(n-2 + ... + sqrt(1)))).
double nested_sqrt(int n) {
    if (n == 1) {
        return sqrt(1.0); 
    }
    else {
        return sqrt(n + nested_sqrt(n - 1)); 
    }
}

int double_factorial(int m) {
    if (m <= 0) {
        return 1; 
    }
    else {
        return m * double_factorial(m - 2); 
    }
}

int main() {
    int task;
    int n, m;
    double result;
    while (true) {
        printf("Input task (1 or 2): ");
		scanf_s("%d", &task);
        switch (task)
        {
        case 1:
            printf("Input n: ");
            if (scanf_s("%d", &n) != 1 || n <= 0) {
                printf("Error: n must be a positive integer.\n");
                return 1;
            }
            result = getSx(n);
            printf("Result Sx: %.6f\n", result);
            break;

        case 2:
            printf("Input n: ");
            if (scanf_s("%d", &n) != 1 || n <= 0) {
                printf("Error: n must be a positive integer.\n");
                return 1;
            }

            printf("Input m: ");
            if (scanf_s("%d", &m) != 1 || m <= 0) {
                printf("Error: m must be a positive integer.\n");
                return 1;
            }

            result = nested_sqrt(n) / double_factorial(m);
            printf("Result: %.6f\n", result);
            break;

        default:
            printf("Error: Unknown task number. Please enter 1 or 2.\n");
            break;
        }
    }

    return 0;
}