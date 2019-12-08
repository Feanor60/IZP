 /*
**@author: Vojtech Bubela (xbubel08)
**predmet: IZP
**projekt 3
**VUT FIT
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#TODO --help
void help();

//#TODO --test

typedef struct {
  int rows;
  int cols;
  unsigned char *cells;
} Map;

int main(int argc, char* argv[])
{
    if(argc < 2 || argc > 5)
    {
        fprintf(stderr,"invalid number of arguments\n");
        return 1;
    }else
    {
        fprintf(stdout, "number of arguments is: %d\n", argc);
    }
    
    if(strcmp(argv[1],"--help") == 0)
    {
        help();
        return 0;
    }else{
        fprintf(stdout,"not helping\n");
    }

    FILE *fp;
    char c;

    for(int i = 1; i <=5; i++)
    {
        if(strcmp(argv[i],"soubor.txt"))
        {
           fp = fopen(argv[i],"r");
           break;
        }
    }

    if(fp == NULL)
    {
        fprintf(stderr,"failed to open file\n");
        return 1;
    }else{
        c = fgetc(fp);
        while(c != EOF)
        {
            printf("%c", c);
            c = fgetc(fp);
        }
        printf("\n");
    }

    return 0;
}

void Map_init();

void help()
{
    fprintf(stdout,"                                       ------Guide to proj3------                                   \n");
    fprintf(stdout,"    ______________________________________________________________________________________________\n\n");
    fprintf(stdout,"    run proj3 with '--test soubor.txt' arguments to test if soubor.txt contains valid map         \n");
    fprintf(stdout,"    ______________________________________________________________________________________________\n\n");
    fprintf(stdout,"    run proj 3 with '--rpath R C soubor.txt' arguments to find path through the maze using right  \n");
    fprintf(stdout,"    hand method. R stands for starting row and C stands for starting collumn. You can write       \n");
    fprintf(stdout,"    '--lpath' instead of writing '--rpath' to find path using the left hand method                \n");
    fprintf(stdout,"    ______________________________________________________________________________________________\n\n");
}