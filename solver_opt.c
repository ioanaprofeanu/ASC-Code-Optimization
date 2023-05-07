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
		double *orig_pA = &A[i * N + i];
   		for (j = 0; j < N; j++) {
			double *pA = orig_pA;
			double *pB = &B[j + i * N];
			register double sum = 0;
      		for (k = i; k < N; k++) {
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
	for (i = 0; i < N; i++) {
   		for (j = 0; j < N; j++) {
			register double sum = 0;
      		for (k = j; k < N; k++) {
				// era At[k][j] => inversez cu A[j][k]
				// At - inferior triunghiulara
				sum += AxB[i * N + k] * A[j * N + k];
      		}
			*pAxBxAt++ = sum;
		}
	}

	// Bt×Bt
	// B[i][j] = Bt[j][i]
	register double *pBtxBt = &BtxBt[0];
	for (i = 0; i < N; i++) {
		register double *orig_pBt1 = &B[i * N];
   		for (j = 0; j < N; j++) {
			register double sum = 0;
			register double *pBt1 = orig_pBt1;
			register double *pBt2 = &B[j];
      		for (k = 0; k < N; k++) {
				// ar fi fost de fapt Bt[i][k] * Bt[k][j]; inversez
				sum += *pBt1 * *pBt2;
				pBt1 += N;
				pBt2 ++;
      		}
			*pBtxBt++ = sum;
		}
	}

	// C = (AxBxAt) + (BtxBt)
	pAxBxAt = &AxBxAt[0];
	pBtxBt = &BtxBt[0];
	for (i = 0; i < N; i++) {
   		for (j = 0; j < N; j++) {
			*pAxBxAt++ += *pBtxBt++;
		}
	}

	free(AxB);
	free(BtxBt);
	return AxBxAt;
}
