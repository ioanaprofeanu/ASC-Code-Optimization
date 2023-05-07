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
	// left_result = (AxB)xAt; allocate memory for it
	double *left_result = matrix_allocate_memory(N);

	// calculate AxB
	// copy A into left_result to keep its value
	cblas_dcopy(N * N, A, 1, left_result, 1);
	// calculate AxB, taking into account that A is upper triangular
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, A, N, left_result, N);

	// calculate (AxB)xAt
	// similarly, take into account that A is upper triangular
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1, A, N, left_result, N);

	// right_result = Bt×Bt; allocate memory for it
	double *right_result = matrix_allocate_memory(N);
	// the product is the multiplication of two regular transposed matrices
	cblas_dgemm(CblasRowMajor, CblasTrans, CblasTrans, N, N, N, 1, B, N, B, N, 1, right_result, N);

	// calculate the final result by adding the two matrices;
	// it will be stored in right_result
	cblas_daxpy(N * N, 1, left_result, 1, right_result, 1);

	// free the memory
	free(left_result);

	return right_result;
}
