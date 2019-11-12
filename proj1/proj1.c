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

int hledej_cislo(char tel_cislo[101], char vyhledavaci_parametr[101])
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
                if((int) strlen(vyhledavaci_parametr) == nalezeno)
                {
                    return 1;
                    //break;
                }
                i++;
            }
            else
            {
                nepreruseno = false;
            }

            if(nepreruseno == false && i != 0)
            {
                j--;
            }

            j++;           
                               
        }
            
    }
    return 0;
    
}

bool hledej_jmeno(char jmeno[101], char vyhledavaci_parametr[101])
{
    char cisla_na_pismena[10][6] = {"0+", "1", "2abc", "3def", "4ghi", "5jkl", "6mno", "7pqrs", "8tuv", "9xyz"};
    char pouzivane_znaky[strlen(vyhledavaci_parametr)][6];

   // printf("cisla na pismena: %d", cisla_na_pismena[0][0]);

    for(int i = 0; i < (int) strlen(vyhledavaci_parametr); i++)
    {
        int j = 0;
        while (j <= 9)
        {
            if(vyhledavaci_parametr[i] == cisla_na_pismena[j][0])
            {
                strcpy(pouzivane_znaky[i],cisla_na_pismena[j]);
                //printf("kopirovane: %s", pouzivane_znaky);
                break;
            }
            j++;
        }
    }

    int j = 0;
    while(j <(int) strlen(jmeno))
    {
        int curr_pole = 0;
        int nalezeno = 0;
        while(nalezeno == curr_pole)
        {
            int curr_char = 0;
            while(curr_char <= (int) strlen(pouzivane_znaky[curr_pole]))
            {
                if(pouzivane_znaky[curr_pole][curr_char] == jmeno[j])
                {
                    nalezeno++;

                    if(nalezeno == (int) strlen(vyhledavaci_parametr))
                    return true;

                    break;

                }
                
                curr_char++;
            }
            curr_pole++;

            // if(nalezeno < curr_pole && curr_pole != 0)
            // {
            //     j--;
            // }
            j++;
        }    
    }
    return false;
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

    bool kont_nalezen;
    //bool cislo_vypsano = false;

    while(fgets(z_stdin, 101, stdin) != NULL) //dokud fgets cte z stdin
    {
        strcpy(jmeno, z_stdin); //ulozim lichy radek jako jmeno
        fgets(z_stdin, 101, stdin);
        strcpy(tel_cislo, z_stdin); // ulozim si sudy radek jako cislo

        // fprintf(stderr,"aktualni jmeno: %s\n",jmeno);
        // fprintf(stderr,"aktualni tel cislo: %s\n",tel_cislo);

        if(jmeno[strlen(jmeno) - 1] == '\n') //pokud nacteny string obsahuje new line char tak ho smazu
        {
            jmeno[strlen(jmeno) - 1] = '\0';
        }


        if(tel_cislo[strlen(tel_cislo) - 1] == '\n') //pokud nacteny string obsahuje new line char tak ho smazu
        {
            tel_cislo[strlen(tel_cislo) - 1] = '\0';
        }

        if (hledej_cislo(tel_cislo, vyhledavaci_parametr) || hledej_jmeno(jmeno, vyhledavaci_parametr)) //hledej jmeno docasne nefunguje, jinak by to bylo v podmince
        {   
            fprintf(stdout,"%s, %s\n", jmeno, tel_cislo);
            kont_nalezen = true;
        }

        //TODO: vyhledavani ve jmenech
    }

    if(!kont_nalezen)
    {
        fprintf(stdout,"Not found\n");
    }


    return 0;
}