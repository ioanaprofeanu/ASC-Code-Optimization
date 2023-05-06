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
	double *At = calloc(N * N, sizeof(double));
	if (At == NULL) {
		perror("calloc BtxBt failed");
	}
	double *Bt = calloc(N * N, sizeof(double));
	if (Bt == NULL) {
		perror("calloc BtxBt failed");
	}

	register int i,j,k;

	// At
	for (i = 0; i < N; i++) {
		register double *p_A = &A[i * N];
		register double *p_At = &At[i];
   		for (j = i; j < N; j++) {
	  		*p_At = *p_A;
			p_A++;
			p_At += N;
   		}
	}

	// Bt
	for (i = 0; i < N; i++) {
		register double *p_B = &B[i * N];
		register double *p_Bt = &Bt[i];
   		for (j = 0; j < N; j++) {
	  		*p_Bt = *p_B;
			p_B++;
			p_Bt += N;
   		}
	}

	// A×B
	// A - superior triunghiulara
	register double *p_AxB = &AxB[0];
	for (i = 0; i < N; i++) {
		register double *orig_pA = &A[i * N];
   		for (j = 0; j < N; j++) {
			register double *p_A = orig_pA;
			register double *p_B = &B[j];
			register double sum = 0;
      		for (k = i; k < N; k++) {
				//AxB[i * N + j] += A[i * N + k] * B[k * N + j];
				sum += *p_A * *p_B;
				p_A++;
				p_B += N;
      		}
			*p_AxB = sum;
			p_AxB++;
		}
	}

	// (AxB)xAt
	// A - superior triunghiulara => At - inferior triunghiulara
	// A[i][j] = At[j][i]
	for (i = 0; i < N; i++) {
   		for (j = 0; j < N; j++) {
      		for (k = j; k < N; k++) {
				// era At[k][j] => inversez cu A[j][k]
				// At - inferior triunghiulara
				AxBxAt[i * N + j] += AxB[i * N + k] * At[k * N + j];
      		}
		}
	}

	// Bt×Bt
	// B[i][j] = Bt[j][i]
	for (i = 0; i < N; i++) {
   		for (j = 0; j < N; j++) {
      		for (k = 0; k < N; k++) {
				// ar fi fost de fapt Bt[i][k] * Bt[k][j]; inversez
				BtxBt[i * N + j] += Bt[i * N + k] * Bt[k * N + j];
      		}
		}
	}

	// C = (AxBxAt) + (BtxBt)
	for (i = 0; i < N; i++) {
   		for (j = 0; j < N; j++) {
			AxBxAt[i * N + j] += BtxBt[i * N + j];
		}
	}

	free(AxB);
	free(BtxBt);
	free(At);
	free(Bt);

	return AxBxAt;	
}
