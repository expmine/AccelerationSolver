#include <stdio.h>
#include <stdlib.h>
#include <math.h>  
#include <time.h>

extern int accelsolve(double Vi, double Vf, double T);

// C function for computing
void compute_acceleration_c(double* input_matrix, int* output, int rows) {
    for (int i = 0; i < rows; i++) {
        double Vi = input_matrix[i * 3];
        double Vf = input_matrix[i * 3 + 1];
        double T = input_matrix[i * 3 + 2];

        double temp = Vf - Vi;
        temp = temp * 1000 / 3600;

        double acceleration = (temp) / T;

        output[i] = (int)round(acceleration);
    }
}

void compute_acceleration_asm(double* input_matrix, int* output, int rows) {
    for (int i = 0; i < rows; i++) {
        double Vi = input_matrix[i * 3];
        double Vf = input_matrix[i * 3 + 1];
        double T = input_matrix[i * 3 + 2];

        // Call assembly
        output[i] = accelsolve(Vi, Vf, T);
    }
}

void generate_random_input(double* input_matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        input_matrix[i * 3] = (rand() / (double)RAND_MAX) * 100.0;

        double Vi = input_matrix[i * 3];
        input_matrix[i * 3 + 1] = Vi + ((rand() / (double)RAND_MAX) * 100.0);

        input_matrix[i * 3 + 2] = 5 + ((rand() / (double)RAND_MAX) * 20.0);
    }
}

int main() {
    int rows;
    printf("Enter the number of rows: ");
    scanf_s("%d", &rows);

    double* input_matrix = (double*)malloc(rows * 3 * sizeof(double));
    int* output_c = (int*)malloc(rows * sizeof(int));
    int* output_asm = (int*)malloc(rows * sizeof(int));

    if (!input_matrix || !output_c || !output_asm) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Generate random input values
    generate_random_input(input_matrix, rows);

    clock_t start, end;
    double time_taken_c, time_taken_asm;

    // Measure time for C implementation
    start = clock();
    compute_acceleration_c(input_matrix, output_c, rows);
    end = clock();
    time_taken_c = ((double)(end - start) * 1000) / CLOCKS_PER_SEC;

    // Measure time for assembly implementation
    start = clock();
    compute_acceleration_asm(input_matrix, output_asm, rows);
    end = clock();
    time_taken_asm = ((double)(end - start) * 1000) / CLOCKS_PER_SEC;

    // Display time results
    printf("\nTime taken by C function: %lf ms\n", time_taken_c);
    printf("Time taken by ASM function: %lf ms\n", time_taken_asm);

    // Display a few results for comparison
    printf("\nComparing outputs (C vs ASM):\n");
    for (int i = 0; i < (rows < 50 ? rows : 50); i++) {
        double Vi = input_matrix[i * 3];
        double Vf = input_matrix[i * 3 + 1];
        double T = input_matrix[i * 3 + 2];
        printf("Row %d: Vi = %.2f km/h, Vf = %.2f km/h, T = %.2f s, C = %d, ASM = %d\n",
            i + 1, Vi, Vf, T, output_c[i], output_asm[i]);
    }

    // Free allocated memory
    free(input_matrix);
    free(output_c);
    free(output_asm);

    return 0;
}
