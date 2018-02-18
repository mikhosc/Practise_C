#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern long int MAX_N = 10e6;

typedef struct student_
{
    char first_name[10];
    char last_name[20];
    int semester;
}student;

void save_to_file_students(char *file_name, student A[], int size)
{
    int i;
    FILE *f;
    f = fopen(file_name, "w+");
    if (!f){
        perror("error");
        return;
    }

    fprintf(f, "%d\n", size);
    for (i = 0 ; i < size ; i++)
    {
        fprintf(f, "%s %s %d\n", A[i].first_name, A[i].last_name, A[i].semester);
    }
    fclose(f);
}

student* read_ST_from_file_to_array(char *file_name)
{
    int size,i=0;
    student *S;
    FILE *f;
    f = fopen(file_name, "r+");
    if (!f)
    {
        perror("error");
        return NULL;
    }
    fscanf(f, "%d", &size);

    //printf("%d", size);

    S = (student*)malloc(sizeof(student) * size);
    for (i=0 ; i < size ; i++)
    {
        fscanf(f, "%s %s %d", S[i].first_name, S[i].last_name, &S[i].semester);
    }
    fclose(f);
    return S;
}

student* read_ST_from_file_to_array_BIN(char *file_name)
{
    int size, i;
    FILE *f;
    student *S;
    f = fopen(file_name, "rb+");
    if (!f){
        perror("error");
        return NULL;
    }

    fread(&size, sizeof(int), 1, f);
    S = (student*)malloc(sizeof(student) * size);
    fread(S, sizeof(student), size, f);

    fclose(f);
    return S;
}

void save_to_file_students_BINARY(char* file_name, student A[], int size)
{
    int i;
    FILE *f;
    f = fopen(file_name, "wb+");

    if (!f)
    {
        perror("error");
        return;
    }
    fwrite(&size, sizeof(int), 1, f);
    fwrite(A, sizeof(student), size, f);
    fclose(f);
}

student put_student_position(char *file_name, int pos)
{
    student s;
    FILE *f;
    f = fopen(file_name, "rb+");
    if (!f){
        perror("error");
        return;
    }
    fseek(f, sizeof(int) + sizeof(student) * (pos-1),SEEK_SET);
    fread(&s, sizeof(student), 1, f);
    fclose(f);
    return s;
}

student put_student_position_rev(char *file_name, int pos)
{
    student s;
    FILE *f;
    f = fopen(file_name, "rb+");
    if (!f){
        perror("error");
        return;
    }
    fseek(f, -sizeof(student) * pos,SEEK_END);
    fread(&s, sizeof(student), 1, f);
    fclose(f);
    return s;
}

void ex1(char *txt)
{
    char *s;
    FILE *f;
    f = fopen(txt ,"w+");
    while (scanf("%s", s) != EOF)
    {
        fprintf(f, "%s\n", s);
    }
    fclose(f);
}

void ex2(char *txt)
{
    FILE *f;
    char *s;
    int size,i;
    f = fopen(txt, "r+");
    while (fgetc(f))
    {
        fscanf(f,"%s", s);
        printf("%s", s);
        /*size = strlen(s);
        for (i = 0;i<size - 1 ; i++)
        {
            //if (!( (s[i]>='a' && (s[i]<='z')) || (s[i]>='A' && (s[i]<='Z')) || (s[i]>='0' && (s[i]<='9')) || s[i]==' '))
              //  fputc('_', stdout);
            //else
                //fputc(s[i], stdout);
            printf("%c", s[i]);
        }*/
        puts("");
    }
    fclose(f);
}

void main(void)
{
    char *s="ex1.txt";
    char *file_name = "students2.txt";
    student *S;
    int i;
    //ex1(s);
    //ex2(s);

    student A[4] = { { "Adam", "Kowalski", 3 }, { "James", "Smith", 2 }, { "Artur", "Green", 2 }, { "Roger", "Brown", 1 } };

    save_to_file_students(file_name, A, 4);
    S = read_ST_from_file_to_array(file_name);
    for (i=0;i<4;i++)
    {
        fprintf(stdout, "%s %s %d\n", S[i].first_name, S[i].last_name, S[i].semester);
    }
    free(S);
    S = read_ST_from_file_to_array("jashg.txt");
    free(S);

    puts("");

    save_to_file_students_BINARY("students.bin", A, 4);
    S = read_ST_from_file_to_array_BIN("students.bin");
    for (i=0;i<4;i++)
    {
        printf("%s %s %d\n", S[i].first_name, S[i].last_name, S[i].semester);
    }
    free(S);

    student s1,s2,s3,s4;

    puts("");

    s1 = put_student_position("students.bin", 3);
    printf("%s %s %d\n", s1.first_name, s1.last_name, s1.semester);
    s2 = put_student_position("students2.bin", 3);

    s3 = put_student_position_rev("students.bin",1);
    printf("%s %s %d\n", s3.first_name, s3.last_name, s3.semester);

    //puts("tekst");
    //fputs("tekst", stdout);

}
