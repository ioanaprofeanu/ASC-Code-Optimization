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

	// calculate A×B
	double *AxB = matrix_allocate_memory(N);
	register double *pAxB = &AxB[0];

	for (register int i = 0; i < N; i++) {
		// reference to the origin of the line, to avoid computing it
		// multiple times in the inner loop
		register double *orig_pA = &A[i * N + i];
		register double *orig_pB = &B[i * N];
   		for (register int j = 0; j < N; j++) {
			// reference to the current element
			register double *pA = orig_pA;
			register double *pB = orig_pB + j;
			// initialize the sum
			register double sum = 0;
			// pA will move onto the next column, pB onto the next line
			// take into account that A is upper triangular
	  		for (register int k = i; k < N; k++, pA++, pB += N) {
				sum += *pA * *pB;
	  		}
			*pAxB++ = sum;
		}
	}

	// calculate (AxB)xAt
	double *AxBxAt = matrix_allocate_memory(N);
	register double *pAxBxAt = &AxBxAt[0];

	for (register int i = 0; i < N; i++) {
		// reference to the origin of the line, to avoid
		// unnecessary computations
		register double *orig_pAxB = &AxB[i * N];
   		for (register int j = 0; j < N; j++) {
			// reference to the current element; A is upper triangular
			// and transposed, so we use A[j][k] instead of A[k][j] (we
			// iterate through it by lines instead of columns)
			register double *pAxB = orig_pAxB + j;
			// pA will skip j elements, because A is upper triangular
			register double *pA = &A[j * N + j];
			register double sum = 0;
			// both pAxB and pA will move onto the next column
	  		for (register int k = j; k < N; k++, pAxB++, pA++) {
				sum += *pAxB * *pA;
	  		}
			*pAxBxAt++ = sum;
		}
	}

	// calculate Bt×Bt
	double *BtxBt = matrix_allocate_memory(N);
	register double *pBtxBt = &BtxBt[0];

	for (register int i = 0; i < N; i++) {
		// reference to the origin of the line, to avoid multiple computations
		register double *orig_pBt1 = &B[i];
   		for (register int j = 0; j < N; j++) {
			// reference to the current element; we iterate through B by columns
			// for Bt1 and by lines for Bt2, because they are the transposed
			// version of B
			register double *pBt1 = orig_pBt1;
			register double *pBt2 = &B[j * N];
			register double sum = 0;
			// pBt1 will move onto the next line, pBt2 onto the next column
	  		for (register int k = 0; k < N; k++, pBt1 += N, pBt2++) {
				sum += *pBt1 * *pBt2;
	  		}
			*pBtxBt++ = sum;
		}
	}

	// initialize the start of the left and right members of the calculus
	// of A×B×At+Bt×Bt
	pAxBxAt = &AxBxAt[0];
	pBtxBt = &BtxBt[0];

	for (register int i = 0; i < N; i++) {
   		for (register int j = 0; j < N; j++) {
			// sum the two members
			*pAxBxAt++ += *pBtxBt++;
		}
	}

	// free the memory
	free(AxB);
	free(BtxBt);

	return AxBxAt;
}
