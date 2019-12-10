 /*
**@author: Vojtech Bubela (xbubel08)
**predmet: IZP
**projekt 3
**VUT FIT
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define test_fce printf("test\n");
#define initial_value 0

typedef struct {
  int rows;
  int cols;
  unsigned char *cells;
} Map;

void delete(char*c);//delete later

void help();

Map Map_ctor(int rows, int cols);

void Map_init(Map *m, char*file);

void Map_dtor(Map *m);

bool Test_map(Map *m, int r, int c);

bool is_border(Map *map, int r, int c, int border);

int main(int argc, char* argv[])
{
    if(argc < 2 || argc > 5)
    {
        fprintf(stderr,"invalid number of arguments\n");
        return 1;
    }
    
    if(strcmp(argv[1],"--help") == 0)
    {
        help();
        return 0;
    }

    FILE *fp;
    char c;
    char *file = "bludiste.txt";

    if(strcmp(argv[argc-1],file)==0)
    {
        fp = fopen(file,"r");
    }else{
        fprintf(stderr,"failed to open file\n");
        return 1;
    }

    int rows;
    int cols;

    if(fp == NULL)
    {
        fprintf(stderr,"failed to open file\n");
        return 1;
    }else{
        fscanf(fp,"%d %d", &rows, &cols);
        c = fgetc(fp);
    }

    Map m = Map_ctor(rows,cols);

    Map_init(&m, file);

    printf("number of rows: %d\nnumber of cols: %d\n", m.rows, m.cols);

    // if(!Test_map(&m))
    // {
    //     fprintf(stderr,"Invalid map\n");
    //     return 1;
    // }    

    delete(&c);
    fclose(fp);
    Map_dtor(&m);
    return 0;
}

void delete(char *c)
{
    *c = 0;
}

Map Map_ctor(int rows, int cols)
{
    Map m;
    m.rows = rows;
    m.cols = cols;

    m.cells = malloc(rows * cols * sizeof(unsigned char));
    if(m.cells == NULL)
        fprintf(stderr,"failed to allocate memory\n");

    return m;
}

void Map_init(Map *m, char*file)
{
    test_fce
    FILE *fpt;
    fpt = fopen(file,"r");

    char c;
    while(c != '\n')
    {
        c = fgetc(fpt);
    }

    for(int i = 0; c != EOF; i++)
    {
        c = fgetc(fpt);
        if(c == ' ' || c == '\n' || c == EOF)
        {
            c = fgetc(fpt);
            if(c == EOF)
                break;
        }
        m->cells[i] = (c - '0');
    }
    fclose(fpt);
}

void Map_dtor(Map *m)
{
  free(m->cells);
}


bool Test_map(Map *m, int r, int c)
{
    bool test;
    unsigned char border = 0;
    while(border < 7)
    {
        dec_to_bin(&border);


        border++;
    }
    return test;
}

bool is_border(Map *m, int r, int c, int border)
{
    bool test = true;

    

    return test;
}

void dec_to_bin(unsigned char *number)
{
    unsigned char temp_number;
    temp_number = *number;

    while()
    {
        if((*number % 2) == 1)
        {
            
        }
    }
}

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