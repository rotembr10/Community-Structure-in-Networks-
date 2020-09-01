#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "community.h"



int delta(int i, int j)
{
	return i == j ? 1 : 0;
}

int kProd(struct _community *C, int i, int j)
{
	return (C->kVec[i] * C->kVec[j]);
}



/* calculate the function f_i^g, i.e., the sum of row i in the matrix B[g].
 * f_i^g = sum_{j}(A_ij) - (k_i/M)*sum_{j}(k_j).
 * Note that because in the project the sparse matrix represent a graph, then:
 * 		sum_{j}(A_ij) equal the number of non-zero elements in row i of matrix A. */
double rowSum(struct _community *C, int i)
{
	int nnz, k_i, M, m;

	nnz = rowNNZ(C->sm, i);
	k_i = C->kVec[i];
	M = C->M;
	m = C->m;

	return nnz - ((double)k_i / M)*m;
}



double rowAbsSum(struct _community *C, int i, int* row)
{
	int n, nnz, j, k, r, M;
	double absSum, f_i;

	M = C->M;
	/* n = number of rows = number of columns  in sparse matrix A */
	n = C->sm->n;
	/* nnz = number of non-zero elements in row i */
	nnz = rowNNZ(C->sm, i);

	/*Calculate row i of the sparse matrix A*/
	for (j = 0; j < n; j++)
	{
		row[j] = 0;
	}
	if (nnz != 0)
	{
		k = C->sm->rowptr[i]; /* k = the index of the first non-zero element */
		for (r = 0; r < nnz; r++)
		{
			row[C->sm->colind[k]] = 1;
			k++;
		}
	}

	/* Calculate the sum in absolute values of row i of B^hat[g] */
	absSum = 0;
	f_i = rowSum(C, i);
	for (j = 0; j < n; j++)
	{
		absSum += fabs((row[j]) - ((double) kProd(C, i, j) / M) - ((double) delta(i, j) * f_i));
	}

	return absSum;
}



community* create_community(spmat* sm, int* originalIndices, int* kVec, int m, int M)
{
	community* C = (community*) malloc(sizeof(community));
	C->sm = sm;
	C->originalIndices = originalIndices;
	C->kVec = kVec;
	C->m = m;
	C->M = M;

	return C;
}



void free_community(community* C)
{
	C->sm->free(C->sm);
	free(C->kVec);
	free(C->originalIndices);
	free(C);
}



/* Note that B^hat[g] is a symmetric matrix, therefore (sum of row i) = (sum of column i). */
void matrixShifting(community* C)
{
	int i, n;
	int* row;
	double curSum, maxSum;

	n = C->sm->n;
	row = malloc(n * sizeof(int));
	maxSum = -1; /* since we sum absolute numbers the sum will be at least 0,
	 	 	 	 	 therefore in the first iteration of the for-loop maxSum's value will update to
	 	 	 	 	 of the sum in absolute numbers of the first column */
	for (i = 0; i < n; i++)
	{
		curSum = rowAbsSum(C, i, row);
		if (curSum > maxSum)
		{
			maxSum = curSum;
		}
	}
	free(row);

	C->norm1 = maxSum;
}
