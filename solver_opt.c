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

	register int i,j,k, bi, bj, bk, blockSize = 40;

	// A×B
	// A - superior triunghiulara
	// for (i = 0; i < N; i++) {
   	// 	for (j = 0; j < N; j++) {
    //   		for (k = i; k < N; k++) {
	// 			AxB[i * N + j] += A[i * N + k] * B[k * N + j];
    //   		}
	// 	}
	// }

	for (bi = 0; bi < N; bi += blockSize) {
        for (bj = 0; bj < N; bj += blockSize) {
            for (bk = 0; bk < N; bk += blockSize) {
                for (i = 0; i < blockSize; i++) {
                    for (j = 0; j < blockSize; j++) {
						//!!!!!!!!!!!!!!!!!!!!!! vezi cum faci sa tii cont ca e sup triunghiulara
                        for (k = 0; k < blockSize; k++) {
							AxB[(bi + i) * N + bj + j] += A[(bi + i) * N + bk + k] * B[(bk + k) * N + bj + j];
						}
					}
				}
			}
		}
	}
			

	// (AxB)xAt
	// A - superior triunghiulara => At - inferior triunghiulara
	// A[i][j] = At[j][i]
	// for (i = 0; i < N; i++) {
   	// 	for (j = 0; j < N; j++) {
    //   		for (k = j; k < N; k++) {
	// 			// era At[k][j] => inversez cu A[j][k]
	// 			// At - inferior triunghiulara
	// 			AxBxAt[i * N + j] += AxB[i * N + k] * A[j * N + k];
    //   		}
	// 	}
	// }
	for (bi = 0; bi < N; bi += blockSize) {
        for (bj = 0; bj < N; bj += blockSize) {
            for (bk = 0; bk < N; bk += blockSize) {
                for (i = 0; i < blockSize; i++) {
                    for (j = 0; j < blockSize; j++) {
						//!!!!!!!!!!!!!!!!!!!!!! vezi cum faci sa tii cont ca e sup triunghiulara
                        for (k = 0; k < blockSize; k++) {
							AxBxAt[(bi + i) * N + bj + j] += AxB[(bi + i) * N + bk + k] * A[(bj + j) * N + bk + k];
						}
					}
				}
			}
		}
	}

	// Bt×Bt
	// B[i][j] = Bt[j][i]
	// for (i = 0; i < N; i++) {
   	// 	for (j = 0; j < N; j++) {
    //   		for (k = 0; k < N; k++) {
	// 			// ar fi fost de fapt Bt[i][k] * Bt[k][j]; inversez
	// 			BtxBt[i * N + j] += B[k * N + i] * B[j * N + k];
    //   		}
	// 	}
	// }

	for (bi = 0; bi < N; bi += blockSize) {
        for (bj = 0; bj < N; bj += blockSize) {
            for (bk = 0; bk < N; bk += blockSize) {
                for (i = 0; i < blockSize; i++) {
                    for (j = 0; j < blockSize; j++) {
                        for (k = 0; k < blockSize; k++) {
							AxB[(bi + i) * N + bj + j] += A[(bk + k) * N + bi + i] * B[(bj + j) * N + bk + k];
						}
					}
				}
			}
		}
	}

	// C = (AxBxAt) + (BtxBt)
	double *orig_AxBxAt = &AxBxAt[0];
	double *orig_BtxBt = &BtxBt[0];
	for (i = 0; i < N; i++) {
   		for (j = 0; j < N; j++) {
			*orig_AxBxAt += *BtxBt;
			orig_AxBxAt++;
			orig_BtxBt++;
		}
	}

	free(AxB);
	free(BtxBt);

	return AxBxAt;	
}
