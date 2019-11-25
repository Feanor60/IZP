/*
**@author: Vojtech Bubela (xbubel08)
**predmet: IZP
**projekt 2
**VUT FIT
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define I_0 1.e-12
#define U_T 25.8563e-3

double storedouble(char *parametr); //rename

double diode(double U_0, double R, double eps);

double vypocet(double U_P, double U_0, double R);

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        fprintf(stderr,"invalidni pocet vstupnich paramentru");
        return 1;
    }

    char *parametr;
    double U_P;

    parametr = argv[1];
    double U_0 = storedouble(parametr);
    parametr = argv[2];
    double R = storedouble(parametr);
    parametr = argv[3];
    double eps = storedouble(parametr);

    U_P = diode(U_0, R, eps); 

    printf("U_0: %g\nR: %g\neps: %g\nU_P: %g\n", U_0, R, eps, U_P);
    return 0;
}

double storedouble(char *parametr) //rename
{
    char *endpointer = NULL; 
    double ntr = strtod(parametr, &endpointer);

    if(*endpointer != '\0')
    {
        fprintf(stderr,"not a double");
        return 1;
    }

    fprintf(stdout,"argument: %g\n", ntr);

    return ntr;
}

double diode(double U_0, double R ,double eps)
{
    double a = 0;
    double b = U_0;
    double c;
    int num_of_iterations;
    int max_num_of_iterations = 1000;

    if(a > b)
    {
        fprintf(stderr,"invalid arguments\n");
        return 1;
    }
    
    while (num_of_iterations <= max_num_of_iterations)
    {
        c = (a+b)/2;//new midpoint

        if (vypocet(c, b, R) == 0 || (b-a)/2 < eps)//found
        {
            return c;
        }

        if(vypocet(c, b, R) < 0 && vypocet(c, a, R) < 0)
            a = c;
        else
            b = c;

        num_of_iterations++;

        if(num_of_iterations == max_num_of_iterations)
        {
            fprintf(stderr,"dosazen maximalni pocet iteraci");
            return 1;
        }   
    }

    printf("U_P: %g, U_0: %g, eps: %g", c, U_0, eps);
    return c;
}

double vypocet(double U_P, double U_0, double R)
{
    return (I_0 * (exp(U_P / U_T) - 1) - ((U_0 - U_P) / R));
}