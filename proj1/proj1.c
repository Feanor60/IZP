#include <stdio.h>
#include <string.h>


void vypis_kontakty()
{
    char from_seznam[101];
    int radky = 1; //pocitadlo na radky

    while(fgets(from_seznam, 101, stdin) != 0)
    {
        from_seznam[strlen(from_seznam) - 1] = '\0';
        
        if(radky % 2 == 1) //pokud je zbytek po deleni dvema 1 tak se jedna o lichy radek
        {
            printf("%s, ", from_seznam);
        }else{
            printf("%s\n", from_seznam);
        }
    radky++; //posunu se na dalsi radek
    }       
}

int main(int argc, char *argv[])
{
    char *vyhledavaci_parametr = argv[1];

    //nacteni a kontrola vyhledavacich parametru
    if(vyhledavaci_parametr==NULL)
    {
       vypis_kontakty();
    }

    
    //cyklus pro hledani v seznam.txt
    
    //vypis nalezenych kontaktu

    //nic nenalezeno

    

    printf("pocet argumentu v argc: %d\n", argc);

    return 0;
}