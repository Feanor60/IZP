#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    //nacteni a kontrola vyhledavacich parametru
    char *vyhledavaci_parametr = argv[1];

    if(vyhledavaci_parametr==NULL)
    {
        //vypsat vsechny kontakty
    }

    printf("vyhledavaci parametr je: %s\n", vyhledavaci_parametr);

    //cyklus pro hledani v seznam.txt, vypis nalezenych kontaktu

    

   printf("%d\n", argc);

    return 0;
}