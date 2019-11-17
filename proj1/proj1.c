/*
**@author: Vojtech Bubela (xbubel08)
**predmet: IZP
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

int hledej_cislo(char tel_cislo[MAX_DELKA_POLE], char vyhledavaci_parametr[MAX_DELKA_POLE])
{
    int j = 0;

    while(j <= (int) strlen(tel_cislo))
    {
        bool nepreruseno = true; //kontroluje zda je dodrzena posloupnost
        int nalezeno = 0;
        int i = 0;
        
        while(nepreruseno)//kontroluje neprerusenou posloupnost
        {
            if(vyhledavaci_parametr[i] == tel_cislo[j])//porovnava jednotlive znaky
            {
                nalezeno++;//pokud se znaky rovnaji, pocitadlo znaku se zvetsi
                if((int) strlen(vyhledavaci_parametr) == nalezeno)//kontroluje jestli byli nalezeny vsechny prvky vyhledavaciho argumentu
                {
                    return 1;
                }
                i++;
            }
            else
            {
                nepreruseno = false;//posloupnost byla prerusena
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

bool hledej_jmeno(char jmeno[MAX_DELKA_POLE], char vyhledavaci_parametr[MAX_DELKA_POLE])
{
    char cisla_na_pismena[10][6] = {"0+", "1", "2abc", "3def", "4ghi", "5jkl", "6mno", "7pqrs", "8tuv", "9xyz"};
    //stringy znaku ktere predstavuji alternativy pro cisla
    char pouzivane_znaky[strlen(vyhledavaci_parametr)][6];//stringy, se kterymi se prave pracuje

    for(int i = 0; i < (int) strlen(vyhledavaci_parametr); i++)//loop zjisti jake stringy znaku budu potrebovat
    {
        int j = 0;
        while (j <= 9)
        {
            if(vyhledavaci_parametr[i] == cisla_na_pismena[j][0])
            {
                strcpy(pouzivane_znaky[i],cisla_na_pismena[j]);
                break;
            }
            j++;
        }
    }

    char temp_jmeno[MAX_DELKA_POLE];//docasne pole pro praci se jmenem
    strcpy(temp_jmeno,jmeno);

    for(int i = 0; temp_jmeno[i]; i++)
    {
        temp_jmeno[i] = tolower(temp_jmeno[i]);//prevod jmena na male pismena
    }

    int j = 0;
    while(j < (int) strlen(temp_jmeno))//projde cele jmeno
    {
        int curr_pole = 0;
        int nalezeno = 0;
        while(nalezeno == curr_pole)//kontroluje neprerusenou posloupnost
        {
            int curr_char = 0;
            while(curr_char <= (int) strlen(pouzivane_znaky[curr_pole]))
            {
                if(pouzivane_znaky[curr_pole][curr_char] == temp_jmeno[j])//porovna znaky ze urciteho stringu se znakem ve jmene
                {
                    nalezeno++;

                    if(nalezeno == (int) strlen(vyhledavaci_parametr))//pokud byli v neprerusene posloupnosti nalezeny vsechny
                        return true;

                    break;
                }
                
                curr_char++;
            }
            curr_pole++;

            if(nalezeno < curr_pole && curr_pole != 1)
            {
                j--;
            }
            
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

    char jmeno[MAX_DELKA_POLE];
    char tel_cislo[MAX_DELKA_POLE];
    char z_stdin[MAX_DELKA_POLE];

    bool kont_nalezen;

    while(fgets(z_stdin, MAX_DELKA_POLE, stdin) != NULL) //dokud fgets cte z stdin
    {
        strcpy(jmeno, z_stdin); //ulozim lichy radek jako jmeno
        fgets(z_stdin, MAX_DELKA_POLE, stdin);
        strcpy(tel_cislo, z_stdin); // ulozim si sudy radek jako cislo

        if(jmeno[strlen(jmeno) - 1] == '\n') //pokud nacteny string obsahuje new line char tak ho smazu
        {
            jmeno[strlen(jmeno) - 1] = '\0';
        }


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