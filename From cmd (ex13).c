#include <stdio.h>
#include <stdlib.h>

int** alloc2D(int n, int m)
{
    int **A, i;
    A = (int**)malloc(sizeof(int*) * n);
    for (i = 0 ; i < m ; i++)
    {
        A[i] = (int*)malloc(sizeof(int) * m);
    }

    return A;
}

void free2D(int** A)
{
    int i;
    int size;
    size = sizeof(*A[0]);
     printf("size: %d\n", size);

    free(A);


}

int main(int argc, char **argv)
{
    int i;
    char type;

    printf("number of strings %d\n", argc);

    printf("Name: %s \n", argv[0]);

    for (i = 1; i < argc ; i++)
    {
        printf("%s ", argv[i]);
    }

    //puts("");

    int **A;
    A = alloc2D(2, 3);

    for (i = 0 ; i<2; i++)
    {
        for (int j=0;j<3;j++)
        {
            A[i][j]=i+j;
            printf("%d ", A[i][j]);
        }
        puts("");
    }

    free2D(A);

    // number of arguments should be equal to 3 ex (prog_name, x, 123)
    if (argc != 3)
        puts("Wrong number of arguments");
    else
    {
        type = argv[1][0];

        switch (type)
        {
        case 'd':
            {
                printf("%d", atoi(argv[2]));
                break;
            }
        case 'x':
            {
                printf("%x", atoi(argv[2]));
                break;
            }
        case 'o':
            {
                printf("%o", atoi(argv[2]));
                break;
            }

        default:
            puts("Bad numerical system");

        }
    }

    return 0;
}
