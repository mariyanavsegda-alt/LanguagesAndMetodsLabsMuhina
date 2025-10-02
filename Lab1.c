#include <stdio.h>
#include <math.h>

double calculateZ(double x, double y) {
    if (x * y * y < 2) {
        // Z = min(1 - sin(x² + y³), √(x²))
        double term1 = 1 - sin(x * x + y * y * y);
        double term2 = sqrt(x * x);
        return (term1 < term2) ? term1 : term2;
    } else {
        // Z = √(x² * y + 8)
        return sqrt(x * x * y + 8);
    }
}

int main() {
    double hx = 0.5;
    double hy = 1.2;
    double xn = 0.2;
    double xk = 1.0;
    double yn = 1.0;
    double yk = 3.0;
    
    double sum = 0.0;
    int count = 0;
  
    printf("Значения Z > 0.2:\n");
    printf(" x\t y\t Z\n");
    printf("-------------------\n");
    for (double x = xn; x <= xk + 0.0001; x += hx) {
          for (double y = yn; y <= yk + 0.0001; y += hy) {
            double z = calculateZ(x, y);
            
            if (z > 0.2) {
                sum += z;
                count++;
                printf("%.2f\t%.2f\t%.6f\n", x, y, z);
            }
        }
    }
    
    printf("\n");
    printf("Количество значений Z > 0.2: %d\n", count);
    printf("Сумма значений Z > 0.2: %.6f\n", sum);
    
    return 0;
}
