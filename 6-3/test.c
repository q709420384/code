#include<stdio.h>
#define ARRAYSIZE 4

float mean(float, float);

int main()
{
    int i;
    float a=4.5;
    float b=5.5;
    float rlt=0.0;

    float array_a[ARRAYSIZE]={1.0, 2.0, 3.0, 4.0};
    float array_b[ARRAYSIZE]={4.0, 3.0, 2.0, 1.0};
    float array_rlt[ARRAYSIZE];

    for(i = 0; i < ARRAYSIZE - 1; i++) {
        array_rlt[i] = mean(array_a[i], array_b[i]);
    }

    rlt = mean(a, b);

    return 0;
}
