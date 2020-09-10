#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
//#include <assert.h>
#include "spmat.h"
#include "community.h"
#include "Queue.h"
#include "leadingEigen.h"




#define ZERO 0.00001
#define IS_POSITIVE(X) ((X) > ZERO)



/* -c -fmessage-length=0 -ansi -Wall -Wextra -Werror -pedantic-errors */
int main(int argc, char* argv[])
{

    FILE* file;
    char* inputFileName;
    /*char* outputFileName;*/
    int n, t, i, j, l, M, k_i;
    int* kVec;
    int* orgIndices;
    double* rowVec;
    spmat* sm;
    community* comWholeGraph;
    argc+=0;



    inputFileName = argv[1];
    /*outputFileName = argv[2];*/

    file = fopen(inputFileName, "r");
    if (file == NULL) {
        printf("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    /*n = |V|, i.e., the number of vertices in the graph*/
    t = fread(&n, sizeof(int), 1, file);
    if (t != 1) {
        printf("Failed to read from input file");
        exit(EXIT_FAILURE);
    }

    /*iterate over the input graph to calculate:
     *  'kVec' = vector that contains the degrees of the vertices in the graph
     *  'M' = sum of k_i = the number of non-zero elements in the adjacency matrix*/
    kVec = (int*) malloc(n * sizeof(int));
    M = 0;
    for (i = 0; i < n; i++)
    {
        /*k_i = the degree of vertex i in the graph*/
        t = fread(&k_i, sizeof(int), 1, file);
        if (t != 1) {
            printf("Failed to read from input file");
            exit(EXIT_FAILURE);
        }
        kVec[i] = k_i;
        M += k_i;

        /*skip to the next k_i in the file*/
        t = fseek(file, k_i*sizeof(int) ,SEEK_CUR);
        if (t != 0) {
            printf("Failed to skip parts of the input file");
            exit(EXIT_FAILURE);
        }
    }
    /*if M=0, then (k_i*k_j)/M is Undefined*/
    if (M == 0) {
        printf("Division by zero");
        exit(EXIT_FAILURE);
    }

    /*iterate again over the input graph to calculate:
     * 'sm' = the sparse matrix corresponding the graph
     * */
    rewind(file);
    t = fseek(file, sizeof(int) ,SEEK_CUR);
    if (t != 0) {
        printf("Failed to skip parts of the input file");
        exit(EXIT_FAILURE);
    }
    sm = spmat_allocate_array(n, M);
    rowVec = (double*) malloc(n * sizeof(double));
    for (i = 0; i < n; i++)
    {
        /*k_i = the degree of vertex i in the graph*/
        t = fread(&k_i, sizeof(int), 1, file);
        if (t != 1) {
            printf("Failed to read from input file");
            exit(EXIT_FAILURE);
        }
        /*calculate row i of the matrix and adding it to the sparse matrix*/
        for (j = 0; j < n; j++)
        {
            rowVec[j] = 0;

        }
        for (j = 0; j < k_i; j++)
        {
            t = fread(&l, sizeof(int), 1, file);
            if (t != 1) {
                printf("Failed to read from input file");
                exit(EXIT_FAILURE);
            }
            rowVec[l] = 1;
        }
        sm->add_row(sm, rowVec, i);
    }
    free(rowVec);
    fclose(file);
    /* -finished reading from file- */





    /* create community for the WHOLE graph */
    orgIndices = (int*) malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
    {
        orgIndices[i] = i;
    }
    comWholeGraph = create_community(sm, orgIndices, kVec, M, M);
    printf("%d", comWholeGraph->M);




    free_community(comWholeGraph);


    /*Algorithm 3*/




    /*On a successful execution the main function return 0*/
    return 0;
}






