#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "divisionTwo.h"
#include "community.h"
#include "leadingEigen.h"
#define ZERO 0.00001

double calculateDeltaQ(community* C, double* s)
{
    double res=0,mult=0;
    int i,j,n;
    n = C->sm->n;
    for(i=0;i<n;++i){
        double* B_hat = (double*)calloc(n,sizeof(double));
        calculateBhat(C,&B_hat,i);
        for(j=0;j<n;++j){
            mult += s[j] * B_hat[j];
        }
        res += mult * s[i];
        mult = 0;
        free(B_hat);
    }

    return (double)res/2;
}

int* Algorithm2 (community* C)
{
    int i,n;
    double eigenValue, Q;
    double* eigenVector;
    int* s;

    s = (int*)malloc(n * sizeof(int));
    n = C->sm->n;

    eigenVector = (double*)calloc(n , sizeof(double));
    power_iteration(C,&eigenValue,&eigenVector);

    if(eigenValue<=ZERO)
        return NULL ;
   /*initialize vector s*/
    for (i = 0; i <n ; ++i) {
        if (eigenVector[i] > ZERO) {
            s[i] = 1;
        } else {
            s[i] = -1;
        }
    }
    Q = calculateDeltaQ(C,s);
    if(Q<=ZERO){
        return NULL;
    }
    return s;
}