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
	if (AxB == NULL) {
		perror("calloc AxB failed");
	}

	// A×B
	// A - superior triunghiulara
	for (int i = 0; i < N; i++) {
   		for (int j = 0; j < N; j++) {
      		for (int k = i; k < N; k++) {
				AxB[i * N + j] += A[i * N + k] * B[k * N + j];
      		}
		}
	}

	double *AxBxAt = calloc(N * N, sizeof(double));
	if (AxBxAt == NULL) {
		perror("calloc AxBxAt failed");
	}

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

	double *BtxBt = calloc(N * N, sizeof(double));
	if (BtxBt == NULL) {
		perror("calloc BtxBt failed");
	}

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
