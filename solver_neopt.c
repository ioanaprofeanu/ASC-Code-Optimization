/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("NEOPT SOLVER\n");

	// C=A×B×At+Bt×Bt
	double *AxB = calloc(N * N, sizeof(double));
	double *AxBxAt = calloc(N * N, sizeof(double));
	double *BtxBt = calloc(N * N, sizeof(double));

	int i,j,k;

	// A×B
	// A - superior triunghiulara
	for (i = 0; i < N; i++) {
   		for (j = 0; j < N; j++) {
      		for (k = i; k < N; k++) {
				AxB[i * N + j] += A[i * N + k] * B[k * N + j];
      		}
		}
	}


	// (AxB)xAt
	// A - superior triunghiulara => At - inferior triunghiulara
	// A[i][j] = At[j][i]
	for (i = 0; i < N; i++) {
   		for (j = 0; j < N; j++) {
      		for (k = j; k < N; k++) {
				// era At[k][j] => inversez cu A[j][k]
				// At - inferior triunghiulara
				AxBxAt[i * N + j] += AxB[i * N + k] * A[j * N + k];
      		}
		}
	}

	// Bt×Bt
	// B[i][j] = Bt[j][i]
	for (i = 0; i < N; i++) {
   		for (j = 0; j < N; j++) {
      		for (k = 0; k < N; k++) {
				// ar fi fost de fapt Bt[i][k] * Bt[k][j]; inversez
				BtxBt[i * N + j] += B[k * N + i] * B[j * N + k];
      		}
		}
	}

	// C = (AxBxAt) + (BtxBt)
	for (i = 0; i < N; i++) {
   		for (j = 0; j < N; j++) {
			AxBxAt[i * N + j] += BtxBt[i * N + j];
		}
	}

	free(AxB);
	free(BtxBt);
	return AxBxAt;
}
