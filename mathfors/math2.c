#include <stdio.h>

int main()
{
    int vstup;
    printf("zadejte vstup: ");
    fscanf(stdin,"%d", &vstup);

    int ciselnost = 0;
    int delitelnost = 2;
    int i= 2;
 
    while(vstup > 1)
     {
         if((vstup%i)!=0)
         {
             i++;
         }

         if((vstup%i)==0)
         {
            vstup = vstup/i;
            i = 2;
            ciselnost++;
            printf("vstup: %d, delitel: %d\n",vstup, i);
         }
    }
    printf("ciselnost: %d", ciselnost);

    return 0;
}