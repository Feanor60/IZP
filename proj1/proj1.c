/*
**@author: Vojtech Bubela (xbubel08)
**predmet: IZP
**projekt 1, reseneo s bosusovym zadanim
**VUT FIT
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_DELKA_POLE 101 //pocet znaku nacitanych ze stdin funkci fgets

void vypis_kontakty()
{
    char from_seznam[MAX_DELKA_POLE]; //pole pro docasne ukladani stdin
    unsigned radek = 1; //pocitadlo na radky

    while(fgets(from_seznam, MAX_DELKA_POLE, stdin) != 0) //dokud fgets cte ze stdin
    {
        if(from_seznam[strlen(from_seznam) - 1] == '\n') //pokud nacteny string obsahuje new line char tak ho smazu
        {
            from_seznam[strlen(from_seznam) - 1] = '\0';
        }
        else
        {
            while(getc(stdin) != '\n');//zbavim se neplatnych znaku
        }

        if(radek % 2 == 1) //pokud je zbytek po deleni dvema 1 tak se jedna o radek se jmenem
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

bool hledej_cislo(char tel_cislo[MAX_DELKA_POLE], char vyhledavaci_parametr[MAX_DELKA_POLE])
{
    int i = 0;
   
    for(int j = 0; j <= (int) strlen(tel_cislo); j++)
    {        
        if(vyhledavaci_parametr[i] == tel_cislo[j])//porovnava jednotlive znaky
        {
            if((int) strlen(vyhledavaci_parametr) == i)//kontroluje jestli byli nalezeny vsechny prvky vyhledavaciho argumentu
            {
                return true;
            }
            
            i++;
        }
    }
    return false; 
}

bool hledej_jmeno(char jmeno[MAX_DELKA_POLE], char vyhledavaci_parametr[MAX_DELKA_POLE])//prohleda jmeno
{
    char cisla_na_pismena[10][6] = {"0+", "1", "2abc", "3def", "4ghi", "5jkl", "6mno", "7pqrs", "8tuv", "9xyz"};
    //stringy znaku ktere predstavuji alternativy pro cisla
    char pouzivane_znaky[strlen(vyhledavaci_parametr)][6];//stringy, se kterymi se prave pracuje

    for(int i = 0; i < (int) strlen(vyhledavaci_parametr); i++)//loop zjisti jake stringy znaku budu potrebovat
    {
        for(int j = 0; j <= 9; j++)
        {
            if(vyhledavaci_parametr[i] == cisla_na_pismena[j][0])
            {
                strcpy(pouzivane_znaky[i],cisla_na_pismena[j]);
                break;
            }
        }
    }

    char temp_jmeno[MAX_DELKA_POLE];//docasne pole pro praci se jmenem
    strcpy(temp_jmeno,jmeno);

    for(int i = 0; temp_jmeno[i]; i++)
    {
        temp_jmeno[i] = tolower(temp_jmeno[i]);//prevod jmena na male pismena
    }

    int curr_pole = 0;

    for(int j = 0; j <= (int) strlen(temp_jmeno); j++)//projde cele jmeno
    {
        int curr_char = 0;
        while(curr_char < (int) strlen(pouzivane_znaky[curr_pole]))
        {
            //printf("%d : %d : %d\n", pouzivane_znaky[curr_pole][curr_char], temp_jmeno[j], curr_pole);
            if(pouzivane_znaky[curr_pole][curr_char] == temp_jmeno[j])//porovna znaky ze urciteho stringu se znakem ve jmene
            {
                curr_pole++;
                if(curr_pole == (int) strlen(vyhledavaci_parametr))//pokud byly nalezeny vsechny vyhledavaci znaky funkce vrati true
                {
                    return true;
                }                
                break;
            }
                
            curr_char++;
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

    if(vyhledavaci_parametr==NULL)//pokud nebyl zadan vyhledavaci parametr program vypise vsechny kontakty
    {
       vypis_kontakty();
       return 0;
    }

    char jmeno[MAX_DELKA_POLE];
    char tel_cislo[MAX_DELKA_POLE];
    char z_stdin[MAX_DELKA_POLE];

    bool kont_nalezen;

    while(fgets(z_stdin, MAX_DELKA_POLE, stdin) != NULL) //dokud fgets cte z stdin
    {
        strcpy(jmeno, z_stdin); //ulozim lichy radek jako jmeno

        if(jmeno[strlen(jmeno) - 1] == '\n') //pokud nacteny string obsahuje new line char tak ho smazu
        {
            jmeno[strlen(jmeno) - 1] = '\0';
        }
        else
        {
            while(getc(stdin) != '\n');
        }

        fgets(z_stdin, MAX_DELKA_POLE, stdin);
        strcpy(tel_cislo, z_stdin); // ulozim si sudy radek jako cislo


        if(tel_cislo[strlen(tel_cislo) - 1] == '\n') //pokud nacteny string obsahuje new line char tak ho smazu
        {
            tel_cislo[strlen(tel_cislo) - 1] = '\0';
        }

        //pokud je mezi telefonim cislem (nebo jmenem) a vyhledavacim argumentem nalezena shoda bude vypsan dany kontakt
        if (hledej_cislo(tel_cislo, vyhledavaci_parametr) || hledej_jmeno(jmeno, vyhledavaci_parametr))
        {   
            fprintf(stdout,"%s, %s\n", jmeno, tel_cislo);
            kont_nalezen = true;
        }
    }

    if(!kont_nalezen)
    {
        fprintf(stdout,"Not found\n");
    }

    return 0;
}