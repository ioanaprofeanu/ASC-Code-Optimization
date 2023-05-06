/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include <string.h>
#include "utils.h"
#include "cblas.h"

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");
	// C = (AxB)xAt + (BtxBt)
	double *result = calloc(N * N, sizeof(double));

	// A×B
	// A - superior triunghiulara
	memcpy(result, B, N * N * sizeof(double));
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, A, N, result, N);
	
	// (AxB)xAt
	// A - superior triunghiulara
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1, A, N, result, N);
	
	// C = Bt×Bt + (AxB)xAt
	cblas_dgemm(CblasRowMajor, CblasTrans, CblasTrans, N, N, N, 1, B, N, B, N, 1, result, N);
	
	return result;
}
