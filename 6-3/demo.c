#include <stdio.h>

struct node {
    int element;
};

typedef struct node *PNode;

int main()
{
    int i;
    PNode np=NULL;

    for (i=0; i<10; i++) {
        printf("Hello World!");
    }

    printf("%d \n", np->element);
}

