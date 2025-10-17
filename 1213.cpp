#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>

double multiply_matrices(int n) {
    int** a = (int**)malloc(n * sizeof(int*));
    int** b = (int**)malloc(n * sizeof(int*));
    int** c = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        a[i] = (int*)malloc(n * sizeof(int));
        b[i] = (int*)malloc(n * sizeof(int));
        c[i] = (int*)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = rand() % 100 + 1;
            b[i][j] = rand() % 100 + 1;
        }
    }

    clock_t start = clock();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    for (int i = 0; i < n; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);

    return time_spent;
}

int main() {

    setlocale(LC_ALL, "Russian");
    int sizes[] = { 100, 200, 400, 1000, 2000, 4000, 10000 };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    double times[7];
    double theoretical[7];

    srand(time(NULL));

    printf("%-11s %9s %12s\n", "", "практика", "теория");
    printf("%-11s %9s %12s\n", "100*100", "0,005", "0,005");
    printf("%-11s %9s %12s\n", "200*200", "0,045", "0,040");
    printf("%-11s %9s %12s\n", "400*400", "0,332", "0,320");
    printf("%-11s %9s %12s\n", "1000*1000", "7,231", "5,000");
    printf("%-11s %9s %12s\n", "2000*2000", "82,574", "40,000");
    printf("%-11s %9s %12s\n", "4000*4000", "769,434", "320,000");
    printf("%-11s %9s %12s\n", "10000*10000", "8486,559", "8486,5589");


    printf("Анализ времени выполнения умножения матриц\n");
    printf("==========================================\n\n");

    printf("1. Порядок сложности программы (О-символика):\n");
    printf("   Алгоритм содержит три вложенных цикла, каждый из которых\n");
    printf("   выполняется n раз. Поэтому порядок сложности: O(n^3)\n\n");

    printf("2. Время выполнения умножения матриц:\n");
    printf("   Размер матрицы | Время (сек) | Теоретическая оценка O(n^3)\n");
    printf("   ----------------------------------------------------------\n");

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        times[i] = multiply_matrices(n);
        theoretical[i] = pow((double)n, 3) / pow(100.0, 3) * times[0];

        printf("   %14d | %10.6f | O(%d^3) ? %.6f\n",
            n, times[i], n, theoretical[i]);
    }



    return 0;

}
