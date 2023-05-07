/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include <string.h>
#include "utils.h"
#include "cblas.h"

double *matrix_allocate_memory(int N)
{
	double *matrix = calloc(N * N, sizeof(double));
	if (matrix == NULL) {
		perror("calloc failed");
	}
	return matrix;
}

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");
	// C = (AxB)xAt + (BtxBt)
	double *left_result = matrix_allocate_memory(N);

	// A×B
	// A - superior triunghiulara
	cblas_dcopy(N * N, A, 1, left_result, 1);
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, A, N, left_result, N);
	
	// (AxB)xAt
	// A - superior triunghiulara
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1, A, N, left_result, N);
	
	double *right_result = matrix_allocate_memory(N);
	// C = Bt×Bt + (AxB)xAt
	cblas_dgemm(CblasRowMajor, CblasTrans, CblasTrans, N, N, N, 1, B, N, B, N, 1, right_result, N);
	
	cblas_daxpy(N * N, 1, left_result, 1, right_result, 1);

	return right_result;
}
