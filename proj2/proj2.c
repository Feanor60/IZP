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

double absval(double x);

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        fprintf(stderr,"invalidni pocet vstupnich paramentru");
        return 1;
    }

    char *parametr;
    double Up;
    double Ip;

    parametr = argv[1];
    double U_0 = storedouble(parametr);
    parametr = argv[2];
    double R = storedouble(parametr);
    parametr = argv[3];
    double eps = storedouble(parametr);

    Up = diode(U_0, R, eps);
    Ip = I_0 * (exp(Up / U_T) - 1);

    if(U_0 > 0)
    {
        printf("Up=%g V\n",Up);
        printf("Ip=%g A\n",Ip);
    }else
    {
        fprintf(stderr,"invalid arguments\n");
        return 1;
    }
    
    return 0;
}

double absval(double x)
{
    if(x < 0)
        return -x;
    else
    {
        return x;
    }
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

    // fprintf(stdout,"argument: %g\n", ntr);

    return ntr;
}

double diode(double U_0, double R ,double eps)
{
    double a = 0;
    double b = U_0;
    // double c;
    double middle = (a+b)/2;
    double fmid = vypocet(middle,U_0,R);
    int max_iterac = 1000;
    int iterac = 0;

    while(absval(b - a) > eps)
    {
        if(vypocet(a,U_0,R) * fmid < 0)
            b = middle;
        else
            a = middle;
        
        if(absval(b - a) > eps)
        {
            middle = (a+b)/2;
            fmid = vypocet(middle, U_0, R);
        }

        if(iterac == max_iterac)
        {
            fprintf(stderr,"too many iterations\n");
            return 1;
        }

        iterac++;
        
    }

    return middle;
    // int num_of_iterations;
    // int max_num_of_iterations = 1000;

    // if(a > b)
    // {
    //     fprintf(stderr,"invalid arguments\n");
    //     return 1;
    // }
    
    // while (num_of_iterations <= max_num_of_iterations)
    // {
    //     c = (a+b)/2;//new midpoint

    //     if (vypocet(c, b, R) == 0 || (b-a)/2 < eps)//found
    //     {
    //         return c;
    //     }

    //     if(vypocet(c, b, R) * vypocet(a, b, R) < 0)
    //     {
    //         a = c;
    //         printf("-");
    //     }    
    //     else
    //     {
    //         b = c;
    //         printf("+");
    //     }
    //     num_of_iterations++;

    //     printf("middle: %g\n",c);

    //     if(num_of_iterations == max_num_of_iterations)
    //     {
    //         fprintf(stderr,"dosazen maximalni pocet iteraci");
    //         return 1;
    //     }   
    // }

    // return 0;
}

double vypocet(double U_P, double U_0, double R)
{
    return (I_0 * (exp(U_P / U_T) - 1)) - ((U_0 - U_P) / R);
}