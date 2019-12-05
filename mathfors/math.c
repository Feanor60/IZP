#include <stdio.h>

int main()
{
    int hodnota;
    int temp_hodnota;//prechodna hodnota, kteroa se bude pouzivat na vypocty
    int zaklad;
    int cislice;

    printf("zadejte hodnotu: ");
    fscanf(stdin, "%d", &hodnota);

    printf("zadejte zaklad: ");
    fscanf(stdin, "%d", &zaklad);

    printf("zadejte cislici: ");
    fscanf(stdin, "%d", &cislice);

    temp_hodnota = hodnota; //s temp_hodnotou budeme dale pocitat

    int zbytek = 0;
    int pocitadlo = 1;
    int muj_vysledek = 0;
    int found = 0; //promena pro hledani cislice

   
    for(;temp_hodnota != 0;pocitadlo++)//dokud nedojdu na konec deleni, tj. temp_hodnota == 0
    {
        zbytek = temp_hodnota % zaklad; //ulozim si zbytek po deleni

        temp_hodnota = temp_hodnota / zaklad;//vydelim

        if(zbytek == cislice)//jestli behem deleni najdu cislo co hledam tak si ulozim jeho pocizi
        {
            pocitadlo = muj_vysledek;//pocitadlo = kolikrat sem hodnotu delil zakladem, muj_vysledek = zaznamenam si pozici na ktere sem nasel vysledek
            found = 1;//cislo sem nasel a tedy ho pak muzu vypsat
        }
    }

    if(found == 1)//od zelkoveho poctu deleni (pocitadlo) odectu muj_vysledek a dostanu tedy pozici na ktere se nachazi hledane cislo
        printf("V zapisu v pravidelnem posicni soustave o zakladu %d cisla %d je cislice %d na %d. pozici.\n", zaklad, hodnota, cislice, (pocitadlo - muj_vysledek));
            
    if(found == 0)//nebylo nalezeno ani jedno hledane cislo
        printf("V zapisu v pravidelnem posicni soustave o zakladu %d cisla %d nebyla cislice %d nalezena\n", zaklad, hodnota, cislice);
    

    return 0;

}