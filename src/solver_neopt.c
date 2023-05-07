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

	// calculate AxB
	double *AxB = matrix_allocate_memory(N);

	for (int i = 0; i < N; i++) {
   		for (int j = 0; j < N; j++) {
			// take into account that A is upper triangular;
			// we don't access the zeros
	  		for (int k = i; k < N; k++) {
				AxB[i * N + j] += A[i * N + k] * B[k * N + j];
	  		}
		}
	}

	// calculate AxBxAt
	double *AxBxAt = matrix_allocate_memory(N);

	for (int i = 0; i < N; i++) {
   		for (int j = 0; j < N; j++) {
			// take into account that A is upper triangular
	  		for (int k = j; k < N; k++) {
				// we should At[k][j], so we use A[j][k]
				// to transverse the matrix
				AxBxAt[i * N + j] += AxB[i * N + k] * A[j * N + k];
	  		}
		}
	}

	// calculate BtxBt
	double *BtxBt = matrix_allocate_memory(N);

	for (int i = 0; i < N; i++) {
   		for (int j = 0; j < N; j++) {
	  		for (int k = 0; k < N; k++) {
				// we should have Bt[i][k] * Bt[k][j]; so we swich
				// the indexes to transverse the matrices
				BtxBt[i * N + j] += B[k * N + i] * B[j * N + k];
	  		}
		}
	}

	// sum up the two sides of the calculus
	// to get the final result
	double *result = matrix_allocate_memory(N);
	for (int i = 0; i < N; i++) {
   		for (int j = 0; j < N; j++) {
			result[i * N + j] += AxBxAt[i * N + j] + BtxBt[i * N + j];
		}
	}

	// free the memory
	free(AxB);
	free(BtxBt);
	free(AxBxAt);

	return result;
}
