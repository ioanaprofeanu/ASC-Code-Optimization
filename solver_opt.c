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


	return AxBxAt;	
}
