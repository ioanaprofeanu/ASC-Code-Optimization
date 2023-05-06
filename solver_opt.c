/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("OPT SOLVER\n");

	// C=A×B×At+Bt×Bt
	double *AxB = calloc(N * N, sizeof(double));
	if (AxB == NULL) {
		perror("calloc AxB failed");
	}
	double *AxBxAt = calloc(N * N, sizeof(double));
	if (AxBxAt == NULL) {
		perror("calloc AxBxAt failed");
	}
	double *BtxBt = calloc(N * N, sizeof(double));
	if (BtxBt == NULL) {
		perror("calloc BtxBt failed");
	}

	register int i,j,k;

	// A×B
	// A - superior triunghiulara
	register double *pAxB = &AxB[0];
	for (i = 0; i < N; i++) {
   		for (j = 0; j < N; j++) {
			register double sum = 0;
      		for (k = i; k < N; k++) {
				sum += A[i * N + k] * B[k * N + j];
      		}
			*pAxB++ = sum;
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
