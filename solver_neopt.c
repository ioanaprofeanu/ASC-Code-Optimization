/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include "utils.h"

double *matrix_allocate_memory(int N)
{
	double *matrix = calloc(N * N, sizeof(double));
	if (matrix == NULL) {
		perror("calloc failed");
	}
	return matrix;
}

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("NEOPT SOLVER\n");

	// C=A×B×At+Bt×Bt
	double *AxB = matrix_allocate_memory(N);

	// A×B
	// A - superior triunghiulara
	for (int i = 0; i < N; i++) {
   		for (int j = 0; j < N; j++) {
      		for (int k = i; k < N; k++) {
				AxB[i * N + j] += A[i * N + k] * B[k * N + j];
      		}
		}
	}

	double *AxBxAt = matrix_allocate_memory(N);
	// (AxB)xAt
	// A - superior triunghiulara => At - inferior triunghiulara
	// A[i][j] = At[j][i]
	for (int i = 0; i < N; i++) {
   		for (int j = 0; j < N; j++) {
      		for (int k = j; k < N; k++) {
				// era At[k][j] => inversez cu A[j][k]
				// At - inferior triunghiulara
				AxBxAt[i * N + j] += AxB[i * N + k] * A[j * N + k];
      		}
		}
	}

	double *BtxBt = matrix_allocate_memory(N);
	// Bt×Bt
	// B[i][j] = Bt[j][i]
	for (int i = 0; i < N; i++) {
   		for (int j = 0; j < N; j++) {
      		for (int k = 0; k < N; k++) {
				// ar fi fost de fapt Bt[i][k] * Bt[k][j]; inversez
				BtxBt[i * N + j] += B[k * N + i] * B[j * N + k];
      		}
		}
	}

	// C = (AxBxAt) + (BtxBt)
	for (int i = 0; i < N; i++) {
   		for (int j = 0; j < N; j++) {
			AxBxAt[i * N + j] += BtxBt[i * N + j];
		}
	}

	free(AxB);
	free(BtxBt);
	return AxBxAt;
}
