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
	double *AxBxAt = calloc(N * N, sizeof(double));
	if (AxBxAt == NULL) {
		perror("calloc AxBxAt failed");
	}
	double *BtxBt = calloc(N * N, sizeof(double));
	if (BtxBt == NULL) {
		perror("calloc BtxBt failed");
	}
	double *At = calloc(N * N, sizeof(double));
	if (At == NULL) {
		perror("calloc BtxBt failed");
	}
	double *Bt = calloc(N * N, sizeof(double));
	if (Bt == NULL) {
		perror("calloc BtxBt failed");
	}

	int i,j,k;

	// At
	for (i = 0; i < N; i++) {
   		for (j = i; j < N; j++) {
	  		At[j * N + i] = A[i * N + j];
   		}
	}

	// Bt
	for (i = 0; i < N; i++) {
   		for (j = 0; j < N; j++) {
	  		Bt[j * N + i] = B[i * N + j];
   		}
	}

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
      		for (k = 0; k <= i; k++) {
				// era At[k][j] => inversez cu A[j][k]
				// At - inferior triunghiulara
				AxBxAt[i * N + j] += AxB[i * N + k] * At[k * N + j];
      		}
		}
	}

	// Bt×Bt
	// B[i][j] = Bt[j][i]
	for (i = 0; i < N; i++) {
   		for (j = 0; j < N; j++) {
      		for (k = 0; k < N; k++) {
				// ar fi fost de fapt Bt[i][k] * Bt[k][j]; inversez
				BtxBt[i * N + j] += Bt[i * N + k] * Bt[k * N + j];
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
	free(At);
	free(Bt);

	return AxBxAt;
}
