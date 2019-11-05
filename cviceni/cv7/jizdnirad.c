#include <stdio.h>
#include <string.h>

struct time_t
{
    int hour;
    int minute;
};

struct jizdni_rad
{
    char zastavka[20][20];
    int dojezdDalsi[20];
    struct time_t vyjezdy[20];
};

int main(int argc,char *argv[])
{
    
    struct jizdni_rad jizdnirad1;

    for(int nta_zastavka = 0; nta_zastavka <= 20; nta_zastavka++)
    {
        int i;
        int nty_znak = 0;

        if(i == '\n')
        {
            break;
        }

        while((i = fgetc(stdin)) != ' ' && i != '\n')
        {
            jizdnirad1.zastavka[nta_zastavka][nty_znak] = i;
            nty_znak++;
        }
    }

    for(int nta_zastavka = 0; nta_zastavka <= 20; nta_zastavka++)
    {
        int i;
        int nty_znak = 0;


        while((i = fgetc(stdin)) != ' ' && i != '\n')
        {
            int nty_znak = 0;
            jizdnirad1.dojezdDalsi[nty_znak]= i;
            nty_znak++;
        }
        
        if(i == '\n')
        {
            break;
        }
    }

    printf("%d %s",argc, argv[1]);

        return 0;
}


