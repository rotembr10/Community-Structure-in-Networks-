#include <stdio.h>
#include <stdlib.h>
#include "spmat.h"

void add_row_array (struct _spmat *A, const double *row, int i) {

	int nnz_i; /*number of non-zero elements in the matrix until row i (excluding row i)*/
	int j;

	nnz_i = (i == 0) ? 0 : (A->rowptr)[i-1];
	while ((A->values)[nnz_i] != 0) {
		nnz_i += 1;
	}
	(A->rowptr)[i] = nnz_i;

	for (j = 0; j < (A->n); j++) {
		if (row[j] == 0) {
			continue;
		}
		(A->values)[nnz_i] = row[j];
		(A->colind)[nnz_i] = j;
		nnz_i += 1;
	}

}

void free_array (struct _spmat *A) {
	free((A->values));
	free((A->colind));
	free((A->rowptr));
	free(A);
}

void mult_array (const struct _spmat *A, const double *v, double *result) {
	int nnz_i;
	int i, j, k, sum;

	/*calculating the vector 'result'*/
	for (i = 0; i < (A->n); i++)
	{
		nnz_i = (A->rowptr)[i+1] - (A->rowptr)[i]; 	/*number of non-zero elements in ROW i of the matrix*/
		if (nnz_i == 0) /*if matrix's row i contains only zeros*/
		{
			result[i] = 0;
		}
		else
		{
			k = (A->rowptr)[i]; /*k is the index of the of the first element in row i of the matrix
									in the 'values' array*/
			sum = 0;
			for (j = 0; j < nnz_i; j++)
			{
				sum += ((A->values)[k] * v[(A->colind)[k]]);
				k++;
			}
			result[i] = sum;
		}
	}

}



/* the 'values' array initiated to zeros (0,...,0),
 * the last element of the 'rowptr' array initiated to nnz */
spmat* spmat_allocate_array(int n, int nnz) {
	int i;

	spmat* s = (spmat*) malloc(sizeof(spmat));
	s->n = n;
	s->add_row = add_row_array;
	s->free = free_array;
	s->mult = mult_array;
	s->values = (int*) malloc(nnz * sizeof(int));
	for (i = 0; i < nnz ; i++)
	{
		(s->values)[i] = 0;
	}
	s->colind = (int*) malloc(nnz * sizeof(int));
	s->rowptr = (int*) malloc((n+1) * sizeof(int));
	(s->rowptr)[n] = nnz;

	return s;
}



