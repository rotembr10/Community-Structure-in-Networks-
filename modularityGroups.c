#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "modularityGroups.h"
#include "Queue.h"
#include "community.h"
#include "divisionTwo.h"



void Algorithm3 (community* C)
{
    Queue* P, *O;
    int* s;

    P = createQueue();
    s = Algorithm2(C);
    community* NewC;

}

community* createNewCommunity(community* C, int* s)
{
    community* NewC = create_community()
}

