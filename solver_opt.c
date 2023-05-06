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
	register double sum = 0;

	// A×B
	// A - superior triunghiulara
	register double *p_AxB = &AxB[0];
	for (i = 0; i < N; i++) {
		register double *orig_pA = &A[i * N];
		for (j = 0; j < N; j++) {
			sum = 0;
			register double *pA = orig_pA;
			register double *pB = &B[j];//b[k][j] = b[0][j]
   			for (k = i; k < N; k++) {
				//AxB[i * N + j] += A[i * N + k] * B[k * N + j];
				sum += *pA * *pB;
				pA++;
				pB += N;
      		}
			*p_AxB = sum;
			p_AxB++;
		}
	}

	// for (bi = 0; bi < N; bi += blockSize) {
    //     for (bj = 0; bj < N; bj += blockSize) {
    //         for (bk = 0; bk < N; bk += blockSize) {
    //             for (i = 0; i < blockSize; i++) {
	// 				for (k = 0; k < blockSize; k++) {
	// 					if (k >= i) {
    //                 		for (j = 0; j < blockSize; j++) {
	// 					//!!!!!!!!!!!!!!!!!!!!!! vezi cum faci sa tii cont ca e sup triunghiulara
	// 							AxB[(bi + i) * N + bj + j] += A[(bi + i) * N + bk + k] * B[(bk + k) * N + bj + j];
	// 						}
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// }
			

	// (AxB)xAt
	// A - superior triunghiulara => At - inferior triunghiulara
	// A[i][j] = At[j][i]
	register double *p_AxBxAt = &AxBxAt[0];
	for (i = 0; i < N; i++) {
		register double *orig_pAxB = &AxB[i * N];
   		for (j = 0; j < N; j++) {
			sum = 0;
			register double *pAxB = orig_pAxB;
			register double *pAt = &A[j * N + j];
      		for (k = j; k < N; k++) {
				// era At[k][j] => inversez cu A[j][k]
				// At - inferior triunghiulara
				//AxBxAt[i * N + j] += AxB[i * N + k] * A[j * N + k];
				sum += *pAxB * *pAt;
				pAxB++;
				pAt++;
      		}
			*p_AxBxAt = sum;
			p_AxBxAt++;
		}
	}
	// for (bi = 0; bi < N; bi += blockSize) {
    //     for (bj = 0; bj < N; bj += blockSize) {
    //         for (bk = 0; bk < N; bk += blockSize) {
    //             for (i = 0; i < blockSize; i++) {
	// 				for (k = 0; k < blockSize; k++) {
    //                 	for (j = 0; j < blockSize; j++) {
	// 					//!!!!!!!!!!!!!!!!!!!!!! vezi cum faci sa tii cont ca e sup triunghiulara
	// 						AxBxAt[(bi + i) * N + bj + j] += AxB[(bi + i) * N + bk + k] * A[(bj + j) * N + bk + k];
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// }

	// Bt×Bt
	// B[i][j] = Bt[j][i]
	register double *p_BtxBt = &BtxBt[0];
	for (i = 0; i < N; i++) {
		register double *orig_pBt1 = &B[i];
		for (j = 0; j < N; j++) {
			sum = 0;
			register double *pBt1 = orig_pBt1;
			register double *pBt2 = &B[j * N + j];
   			for (k = 0; k < N; k++) {
				// ar fi fost de fapt Bt[i][k] * Bt[k][j]; inversez
				sum += *pBt1 * *pBt2;
				pBt1 += N;
				pBt2++;
      		}
			*p_BtxBt = sum;
			p_BtxBt++;
		}
	}

	// for (bi = 0; bi < N; bi += blockSize) {
    //     for (bj = 0; bj < N; bj += blockSize) {
    //         for (bk = 0; bk < N; bk += blockSize) {
    //             for (i = 0; i < blockSize; i++) {
	// 				for (k = 0; k < blockSize; k++) {
    //                 	for (j = 0; j < blockSize; j++) {
	// 						AxB[(bi + i) * N + bj + j] += A[(bk + k) * N + bi + i] * B[(bj + j) * N + bk + k];
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// }

	// C = (AxBxAt) + (BtxBt)
	p_AxBxAt = &AxBxAt[0];
	p_BtxBt = &BtxBt[0];
	for (i = 0; i < N; i++) {
   		for (j = 0; j < N; j++) {
			*p_AxBxAt += *p_BtxBt;
			p_AxBxAt++;
			p_BtxBt++;
		}
	}

	free(AxB);
	free(BtxBt);

	return AxBxAt;	
}
