#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void vypis_kontakty()
{
    char from_seznam[101];
    unsigned radek = 1; //pocitadlo na radky

    while(fgets(from_seznam, 101, stdin) != 0)
    {
        from_seznam[strlen(from_seznam) - 1] = '\0';//TODO: pokud nema string newline znak tak ho to o 1 zkrati - opravit
        
        if(radek % 2 == 1) //pokud je zbytek po deleni dvema 1 tak se jedna o lichy radek
        {
            printf("%s, ", from_seznam);
        }
        else
        {
            printf("%s\n", from_seznam);
        }
    radek++; //posunu se na dalsi radek
    }       
}

int main(int argc, char *argv[])
{
    char *vyhledavaci_parametr = argv[1];

    // kontrola poctu vstupnich argumentu
    if (argc > 2)
    {
        fprintf(stderr,"byl zadan vice nez jeden vyhledavaci argument\n");
        return 1;
    }

    if(vyhledavaci_parametr==NULL)
    {
       vypis_kontakty();
       return 0;
    }

    printf("delka vyhledavaciho parametru: %lu\n", strlen(vyhledavaci_parametr));
    //cyklus pro hledani v seznam.txt

    char jmeno[101];
    char tel_cislo[101];
    char z_stdin[101];

    while(fgets(z_stdin, 101, stdin) != NULL) //dokud fgets cte z stdin
    {
        strcpy(jmeno, z_stdin); //ulozim lichy radek jako jmeno
        fgets(z_stdin, strlen(z_stdin), stdin);
        strcpy(tel_cislo, z_stdin); // ulozim si sudy radek jako cislo

        // jmeno[strlen(jmeno) - 1] = '\0'; //TODO: pokud nema string newline znak tak ho to o 1 zkrati - opravit
        // tel_cislo[strlen(tel_cislo) - 1] = '\0';//TODO: pokud nema string newline znak tak ho to o 1 zkrati - opravit

        printf("1\n");
        int j = 0;

        while(j <= (int) strlen(tel_cislo))
        {
            bool nepreruseno = true; //kontroluje zda je dodrzena posloupnost
            int nalezeno = 0; //TODO
            int i = 0;
            // printf("delka tel cisla je: %lu ", strlen(tel_cislo));
            // printf("prave prochazene tel cislo: %s\n", tel_cislo);
        
            while(nepreruseno)
            {
                if(vyhledavaci_parametr[i] == tel_cislo[j])
                {
                    nalezeno++;
                    i++;
                }
                else
                {
                    nepreruseno = false;
                }

                if((int) strlen(vyhledavaci_parametr)==nalezeno)
                {
                    printf("Match, pozice: %s %d\n", tel_cislo, j);
                    break;
                }
                j++;
                
            }
            
        }
    }
   
    //vypis nalezenych kontaktu

    //nic nenalezeno


    return 0;
}