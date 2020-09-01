#include "spmat.h"

#ifndef _COMMUNITY_H
#define _COMMUNITY_H

/* Each struct represents community in the graph */
typedef struct _community {
	/* Pointer to the sparse matrix (A) implemented in spmat.h */
	spmat* sm;

	/* In our implementation, when splitting community C into two sub-communities C1,C2,
	 *  we represent them by 2 new sparse matrices with new indices. for example:
	 *  If C is sparse matrix of size 5x5 corresponding the whole graph with vertices: 0,1,2,3,4,
	 *  and we split C into the communities C1: 0,2 and C2: 1,3,4, we need to remember which vertices
	 *  in the original graph correspond to each community:
	 *  	C1 has sparse matrix 2x2 and indices 0,1 are indices 0,2 in the original matrix
	 *  	C2 has sparse matrix 3x3 and indices 0,1,2 are indices 1,3,4 in the original matrix
	 */
	int* originalIndices;

	/* Vector that contains the degrees of the vertices corresponding the COMMUNITY sm */
	int* kVec;

	/* m = sum of k_i of the COMMUNITY (not the whole graph!), i.e.,
	 *     sum of the degrees of the vertices in subgraph corresponding the community. */
	int m;

	/* M = sum of k_i of the WHOLE graph (not the community!).
	 * All communities have the same M. */
	int M;

	/* This value equal to ||B^hat[g]||_1, i.e., the 1-norm of the matrix of the community.
	 * Calculated by the matrixShifting function in this module. */
	double norm1;
} community;



/* Create new community.
 * You should calculate sm, originalIndices, kVec, m, M and pass them to the function. to calculate
 * norm1 field call the matrixShifting function. */
community* create_community(spmat* sm, int* originalIndices, int* kVec, int m, int M);


/* Frees all resources used by A */
void free_community(community* C);


/* Calculate the function f_i^g, i.e., the sum of row i in the matrix B[g] */
double rowSum(struct _community *C, int i);


/* Calculate and return the sum of row i in absolute values of matrix B^hat[g].
 * Note that B^hat[g] is a symmetric matrix, therefore (sum of row i) = (sum of column i).
 * 'row' is an array of size n the function use in its calculation. The purpose of the parameter
 * 		is to avoid repeated allocation of dynamic memory when calling the function many times,
 * 		for example, to calculate 1-norm of a matrix we need to call the function n times.
 * 		There is NO need to initialize the array 'row' to zeros.
 *		(n is the number of columns in the sparse matrix of the community) */
double rowAbsSum(struct _community *C, int i, int* row);


/* Calculate ||B^hat[g]||_1, i.e., the 1-norm of the matrix of the community, and
 * updating C->norm1 field accordingly */
void matrixShifting(community* C);


/* Return 1 if i=j, else return 0 */
int delta(int i, int j);


/* Return the product k_i*k_j of the community */
int kProd(struct _community *C, int i, int j);





/*  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  */
/* 	!!~~~FUNCTIONS I DIDN'T IMPLEMENT~~~!!  */
/*  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  */
/*  covariance_matrix(); */
/*  power_iteration(); */
/**/
/* According to the method described in previous assignments (covariance matrix and power iteration)
 * this function will calculate and return the dominant eigenvector (the eigenvector with the
 * largest absolute eigenvalue) of the matrix B^hat[g] corresponding the community C
 * AFTER MATRIX SHIFTING. */
double* domEigenVector(community* C);



#endif
