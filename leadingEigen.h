
#ifndef SP_PROJECT_LEADINGEIGEN_H
#define SP_PROJECT_LEADINGEIGEN_H

void createRandVec (double*  b0, int n);
void calculateShiftMatRow(community* C, int i,double* C_i);
void calculateTheNewVec (int n, double* bk, double** next_bk, community* C);
void createEigen (int n, double* bk, double* next_bk, community* C);
void leading_eigen (community* C, double** b1);

#endif //SP_PROJECT_LEADINGEIGEN_H
