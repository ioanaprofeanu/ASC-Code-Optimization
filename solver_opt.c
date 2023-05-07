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

	// A×B
	// A - superior triunghiulara
	register double *pAxB = &AxB[0];
	for (int i = 0; i < N; i++) {
		double *orig_pA = &A[i * N + i];
   		for (int j = 0; j < N; j++) {
			double *pA = orig_pA;
			double *pB = &B[j + i * N];
			register double sum = 0;
      		for (int k = i; k < N; k++) {
				sum += *pA * *pB;
				pA++;
				pB += N;
      		}
			*pAxB++ = sum;
		}
	}

	double *AxBxAt = calloc(N * N, sizeof(double));
	if (AxBxAt == NULL) {
		perror("calloc AxBxAt failed");
	}

	// (AxB)xAt
	// A - superior triunghiulara => At - inferior triunghiulara
	// A[i][j] = At[j][i]
	register double *pAxBxAt = &AxBxAt[0];
	for (int i = 0; i < N; i++) {
		register double *orig_pAxB = &AxB[i * N];
   		for (int j = 0; j < N; j++) {
			register double sum = 0;
			double register *pAxB = orig_pAxB + j;
			double register *pA = &A[j * N + j];
      		for (int k = j; k < N; k++) {
				// era At[k][j] => inversez cu A[j][k]
				// At - inferior triunghiulara
				sum += *pAxB * *pA;
				pAxB++;
				pA++;
      		}
			*pAxBxAt++ = sum;
		}
	}

	double *BtxBt = calloc(N * N, sizeof(double));
	if (BtxBt == NULL) {
		perror("calloc BtxBt failed");
	}
	// Bt×Bt
	// B[i][j] = Bt[j][i]
	register double *pBtxBt = &BtxBt[0];
	for (int i = 0; i < N; i++) {
		register double *orig_pBt1 = &B[i];
   		for (int j = 0; j < N; j++) {
			register double sum = 0;
			double register *pBt1 = orig_pBt1;
			double register *pBt2 = &B[j * N];
      		for (int k = 0; k < N; k++) {
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
	for (int i = 0; i < N; i++) {
   		for (int j = 0; j < N; j++) {
			*pAxBxAt++ += *pBtxBt++;
		}
	}

	free(AxB);
	free(BtxBt);
	return AxBxAt;
}
