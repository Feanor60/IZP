#include <stdio.h>
#include <string.h>

struct date_t{
    int day, month, year;
};

typedef struct pacient_t
{
    char name[30];
    struct date_t birthdate;
    int height;
    int weight;
    char gender[10];
} pacient_t;

int main()
{
    pacient_t *patient1;
    pacient_t pac1;

    patient1 = &pac1;

    strcpy(patient1->name, "Aragorn");

    printf("jmeno pacienta 1: %s\n", patient1->name);


    return 0;
}