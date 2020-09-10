#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "community.h"
#include <assert.h>
#include "leadingEigen.h"



/*calculate the first vector*/
void createRandVec (double*  b0, int n)
{
    int i;
    for (i=0;i<n;i++){
        b0[i] =(double) rand();
    }
}

void calculateShiftMatRow(community* C, int i,double* C_i)
{
    //int n;
    //n = C->sm->n;
    //double* C_i = (double*)calloc(n,sizeof(double));
    C_i[i] = C->norm1;
    calculateBhat(C,&C_i,i);
}

/*calculate the next vector by the given equation*/
void calculateTheNewVec (int n, double* bk, double** next_bk, community* C)
{
    double normAbk=0,sum=0;
    int i,j;
    double* C_i = NULL;


    for(i=0;i<n;i++){
        C_i = (double*)calloc(n,sizeof(double));
        calculateShiftMatRow(C, i,C_i);
        for(j=0;j<n;j++){
            (*next_bk)[i] += C_i[j] * bk[j];
        }
        sum += ((*next_bk)[i]) * ((*next_bk)[i]);
        free(C_i);
    }

    normAbk = sqrt(sum);

    for(i=0;i<n;i++){
        (*next_bk)[i] = (double) ((*next_bk)[i] / normAbk);
    }
}

/*create the eigen vector*/
void createEigen (int n, double* bk, double* next_bk, community* C)
{
    double epsilon = 0.00001;
    int i=0;
    int k;

    while(i<n){
        if(fabs(bk[i]-next_bk[i]) >= epsilon){
            for(k=0;k<n;k++)
                bk[k] = next_bk[k];
            calculateTheNewVec (n,bk,&next_bk,C);
            i=0;
        }
        i++;
    }
}

void leading_eigen (community* C, double** b1)
{
 int n;
 double* b0= NULL;


 n = C->sm->n;

 /*calculate the first vector randomly*/
 b0 = (double*)malloc(n*sizeof(double));
 createRandVec(b0,n);

 /*calculate the second vector according to the equation*/
 calculateTheNewVec (n, b0,b1, C);

 /*create the eigen vector*/
 createEigen (n, b0, *b1, C);

 free(b0);

}
