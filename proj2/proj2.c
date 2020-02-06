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

#define I_0 1.e-12 //zadana konstanta
#define U_T 25.8563e-3 //zadana konstanta

double storedouble(char *parametr);

double diode(double U_0, double R, double eps);

double vypocet(double U_P, double U_0, double R);

double absval(double x);

int main(int argc, char *argv[])
{
    if(argc < 3) //kontrola vstupnich parametru
    {
        fprintf(stderr,"invalidni pocet vstupnich paramentru\n");
        return 1;
    }

    char *parametr;
    double Up;
    double Ip;

    parametr = argv[1]; //nacitani vstupu
    double U_0 = storedouble(parametr); //prevod ze string na double

    if(U_0 < 0) //kontrola vstupnich parametru
    {
        fprintf(stderr,"invalid arguments\n");
        return 1;
    }

    parametr = argv[2];
    double R = storedouble(parametr);

    if(R < 0)
    {
        fprintf(stderr,"invalid arguments\n");
        return 1;
    }

    parametr = argv[3];
    double eps = storedouble(parametr);

    if(eps < 0)
    {
        fprintf(stderr,"invalid arguments\n");
        return 1;
    }

    Up = diode(U_0, R, eps); //vypocet Up
    Ip = I_0 * (exp(Up / U_T) - 1); //vypocet Ip podle vzorce

    printf("Up=%g V\n",Up);
    printf("Ip=%g A\n",Ip);
    
    return 0;
}

double absval(double x)//vrati absolutni hodnotu cisla
{
    if(x < 0)
        return -x;
    else
    {
        return x;
    }
    return 0;
}

double storedouble(char *parametr)//prevod stringu na double
{
    char *endpointer = NULL; 
    double ntr = strtod(parametr, &endpointer);

    if(*endpointer != '\0')//pokud string obsahuje parametry ktere se nedaji ulozit do promenne typu double
    {
        fprintf(stderr,"one of arguments is not a double\n");
        return 1;
    }

    return ntr;
}

double diode(double U_0, double R ,double eps)
{
    double a = 0;
    double b = U_0;
    double middle = (a+b)/2;
    double fmid = vypocet(middle,U_0,R);
    int max_iterac = 1000;//pro kontrolu max poctu iteraci
    int iterac = 0;

    while(absval(b - a) > eps)//dokud nedosahneme pozadovane presnosti
    {
        if(vypocet(a,U_0,R) * fmid < 0)//kontrola jestli je promena a a promena middle na stejne strane intervalu
            b = middle;
        else
            a = middle;
        
        if(absval(b - a) > eps)
        {
            middle = (a+b)/2;//puleni intervalu
            fmid = vypocet(middle, U_0, R);
        }

        if(iterac == max_iterac)//kontrola poctu iteraci
        {
            fprintf(stderr,"too many iterations\n");
            return middle;
        }

        iterac++;
        
    }

    return middle;
    
}

double vypocet(double U_P, double U_0, double R)//vypocet odchylky
{
    return (I_0 * (exp(U_P / U_T) - 1)) - ((U_0 - U_P) / R);
}