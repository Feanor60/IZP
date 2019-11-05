#include <stdio.h>
#include <string.h>
#include <stdbool.h>


void vypis_kontakty()
{
    char from_seznam[101];
    unsigned radek = 1; //pocitadlo na radky

    while(fgets(from_seznam, 101, stdin) != 0)
    {
        if(from_seznam[strlen(from_seznam) - 1] == '\n') //pokud nacteny string obsahuje new line char tak ho smazu
        {
            from_seznam[strlen(from_seznam) - 1] = '\0';
        }

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

void prohledej_seznam(char tel_cislo[101], char vyhledavaci_parametr[101], char jmeno[101])
{
    int j = 0;

    while(j <= (int) strlen(tel_cislo))
    {
        bool nepreruseno = true; //kontroluje zda je dodrzena posloupnost
        int nalezeno = 0; //TODO
        int i = 0;
        
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
                
            j++;

            if((int) strlen(vyhledavaci_parametr) == nalezeno)
            {
                printf("%s %s\n",jmeno, tel_cislo);
                j = (int) strlen(tel_cislo);
                break;
            }
                               
        }
            
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

    //cyklus pro hledani v seznam.txt

    char jmeno[101];
    char tel_cislo[101];
    char z_stdin[101];
    bool cislo_vypsano = false;

    while(fgets(z_stdin, 101, stdin) != NULL) //dokud fgets cte z stdin
    {
        strcpy(jmeno, z_stdin); //ulozim lichy radek jako jmeno
        fgets(z_stdin, strlen(z_stdin), stdin);
        strcpy(tel_cislo, z_stdin); // ulozim si sudy radek jako cislo


        if(jmeno[strlen(jmeno) - 1] == '\n') //pokud nacteny string obsahuje new line char tak ho smazu
        {
            jmeno[strlen(jmeno) - 1] = '\0';
        }


        if(tel_cislo[strlen(tel_cislo) - 1] == '\n') //pokud nacteny string obsahuje new line char tak ho smazu
        {
            tel_cislo[strlen(tel_cislo) - 1] = '\0';
        }

        prohledej_seznam(tel_cislo, vyhledavaci_parametr, jmeno);

        //make void fce form here
        
        // if(!cislo_vypsano)
        // {
        //     printf("Not found\n");
            
        // }
    }
   
    //vypis nalezenych kontaktu

    //nic nenalezeno


    return 0;
}