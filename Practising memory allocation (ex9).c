#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *ex2(int, int ,int);
int *ex3(int);
char *ex4(char *S);
char *ex5(char *A, char *B);

char *ex5(char *A, char *B)
{
    char *S;
    int sizeof_A=0, sizeof_B=0,i=1;

    S = (char*) malloc(1*sizeof(char));
    S[0]='\0';

    while (A[sizeof_A])
    {
        i++;
        S = (char*) realloc(S, i*sizeof(char));
        S[i-2]=A[sizeof_A];
        S[i-1]='\0';
        sizeof_A++;
    }

    while (B[sizeof_B])
    {
        i++;
        S = (char*) realloc(S, i*sizeof(char));
        S[i-2]=B[sizeof_B];
        S[i-1]='\0';
        sizeof_B++;
    }

    return S;
}

char *ex4(char *S)
{
    int i=0,j,k=1;
    char *B;
    B = (char*) malloc(1*sizeof(char));
    B[0]='\0';

    while (S[i])
    {
        if (S[i]!=' ')
        {
            k++;
            B = (char*) realloc(B, sizeof(char)*k);

            B[k-2]=S[i];
            B[k-1]='\0';
        }
        i++;
    }

    return B;
}

int *ex3(int n)
{
    int *A,i=1,p,j;

    A = (int*) calloc(1, sizeof(int));
    A[0]=-1;

    while (n)
    {
        i++;
        p=n%10;
        n/=10;
        A = (int*) realloc(A, sizeof(int)*i);

        for (j=i-1;j>0;j--)
            A[j]=A[j-1];

        A[0]=p;
    }

    return A;
}

int *ex2(int num, int start, int step)
{
    int *A, i;
    A = (int*) malloc(num * sizeof(int));

    if (A==NULL)
        exit(0);

    for (i = 0; i < num; i++)
		A[i] = start + i*step;

    return A;
}


void main(void)
{
    const char *s="a b c d 4 5 2 52 FDSS $", *s1, *A, *conc;
    const char *z="fsdg 252";
    int i=0;

    printf("%s\n", s);
    s1=ex4(s);
    printf("%s\n", s1);
    free(s1);

    //scanf("%s", A);
    //printf("%s\n", A);
    //s1=ex4(A);
    //printf("%s\n", s1);

    //free(s1);

    conc=ex5(s, z);
    printf("%s", conc);
    free(conc);

    /*
    //TASK 3
    int n, *A,i=0;
    puts("Write n");
    scanf("%d", &n);

    A=ex3(n);

    while (A[i]!=-1)
    {
        printf("%d", A[i]);
        i++;
    }

    free(A);

    //TASK 2
    int k,i;
    scanf("%d", &k);

    int *A = ex2(k, 0, 5);

    for (i=0;i<k;i++)
        printf("%d ", A[i]);

    puts("");
    free(A);

    //TASK 1
    int i=0,size=0;
    double sum=0.0;
    double *A;
    puts("Size of an array");
    scanf("%d", &size);

    //A = (double*)malloc(size * sizeof(A));
    A = (double*) calloc(size, sizeof(double));

    for (i=0;i<size;i++)
    {
        scanf("%lf", &A[i]);
        sum+=A[i];
    }

    printf("%lf\n", sum);

    A = (double*) realloc (A, sizeof(double)*size );
    A[size] = 5.0;

    sum+=A[size];

    printf("%lf\n", sum);

    free(A);
    */
}
