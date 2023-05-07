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
 * Add your optimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("OPT SOLVER\n");

	// C=A×B×At+Bt×Bt
	double *AxB = matrix_allocate_memory(N);
	double *AxBxAt = matrix_allocate_memory(N);
	double *BtxBt = matrix_allocate_memory(N);

	// A×B
	// A - superior triunghiulara
	register double *pAxB = &AxB[0];
	for (register int i = 0; i < N; i++) {
		double *orig_pA = &A[i * N + i];
   		for (register int j = 0; j < N; j++) {
			double *pA = orig_pA;
			double *pB = &B[j + i * N];
			register double sum = 0;
      		for (register int k = i; k < N; k++) {
				sum += *pA * *pB;
				pA++;
				pB += N;
      		}
			*pAxB++ = sum;
		}
	}

	// (AxB)xAt
	// A - superior triunghiulara => At - inferior triunghiulara
	// A[i][j] = At[j][i]
	register double *pAxBxAt = &AxBxAt[0];
	for (register int i = 0; i < N; i++) {
		register double *orig_pAxB = &AxB[i * N];
   		for (register int j = 0; j < N; j++) {
			register double sum = 0;
			double register *pAxB = orig_pAxB + j;
			double register *pA = &A[j * N + j];
      		for (register int k = j; k < N; k++) {
				// era At[k][j] => inversez cu A[j][k]
				// At - inferior triunghiulara
				sum += *pAxB * *pA;
				pAxB++;
				pA++;
      		}
			*pAxBxAt++ = sum;
		}
	}

	// Bt×Bt
	// B[i][j] = Bt[j][i]
	register double *pBtxBt = &BtxBt[0];
	for (register int i = 0; i < N; i++) {
		register double *orig_pBt1 = &B[i];
   		for (register int j = 0; j < N; j++) {
			register double sum = 0;
			double register *pBt1 = orig_pBt1;
			double register *pBt2 = &B[j * N];
      		for (register int k = 0; k < N; k++) {
				// ar fi fost de fapt Bt[i][k] * Bt[k][j]; inversez
				sum += *pBt1 * *pBt2;
				pBt1 += N;
				pBt2++;
      		}
			*pBtxBt++ = sum;
		}
	}

	// C = (AxBxAt) + (BtxBt)
	pAxBxAt = &AxBxAt[0];
	pBtxBt = &BtxBt[0];
	for (register int i = 0; i < N; i++) {
   		for (register int j = 0; j < N; j++) {
			*pAxBxAt++ += *pBtxBt++;
		}
	}

	free(AxB);
	free(BtxBt);
	return AxBxAt;
}
