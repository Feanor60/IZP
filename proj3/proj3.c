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
#include <math.h>

#define left_border 1 //0001 bitwise, easy to check in isborder()
#define right_border 2
#define third_border 4
#define up 1
#define down 2
#define right_path 0
#define left_path 1

typedef struct {
  int rows;
  int cols;
  unsigned char *cells;
} Map;

void help(); //prints help

Map Map_ctor(int rows, int cols); //creates map

void Map_init(Map *map, FILE *fp); //inicialize map

void Map_dtor(Map *map); //frees aloccated memory

bool Test_map(Map *map); //test if map from bludiste.txt is valid

bool isborder(Map *map, int r, int c, int border); //return true if there s a border on given coordinate and given

int start_border(Map *map, int r, int c, int leftright); //return border that will be followed

int test_starting_border(Map *map, int r, int c); //tests if i can enter through given coordinate

int follow_right(Map *map, int r, int c, int enter_from); //return border that will be followed if --rpath

int follow_left(Map *map, int r, int c, int enter_from); //return border that will be followed if --lpath

int get_triangle_orient(int r, int c); //return if given coordinate is in triangle that points upwards or downwards

void find_path(Map *map, int r, int c, int starting_side, int path); //prints path using right hand or left hand

void move(int *r, int *c, int passed_through, int move_count); //moves coordinate based on rpath or lapth

bool still_inside(Map *map, int r, int c); //checks if i have escaped the maze

int next_border(int curr_border, int move_count, int path); //returns next border i will check

int main(int argc, char* argv[])
{
    if(argc < 2 || argc > 5)
    {
        fprintf(stderr,"invalid number of arguments\n");
        return 1;
    }
    
    if(strcmp(argv[1],"--help") == 0) //prints help
    {
        help();
        return 0;
    }

    FILE *fp;

    if(strcmp(argv[argc-1],"bludiste.txt") == 0) //if last argument is "bludiste.txt"
    {
        fp = fopen("bludiste.txt","r");
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
        fscanf(fp,"%d %d ", &rows, &cols);
    }

    Map map = Map_ctor(rows,cols); //creates map
    Map_init(&map, fp); //initialize map

    if(strcmp(argv[1],"--test") == 0) //tests map
    {
        if(Test_map(&map))
        {
            printf("valid\n");
            return 0;
        }else{
            printf("invalid\n");
            return 0;
        }
    }

    int leftright = 0; // int to store what path i will follow
    int start_row = 0; //ints to store initial coordinates
    int start_col = 0;
    int path; //int to store what path i will follow

    if(strcmp(argv[1],"--rpath") == 0)
    {
        leftright = right_border;
        start_row = atoi(argv[2]);
        start_col = atoi(argv[3]);
        path = right_path;
    }

    if(strcmp(argv[1],"--lpath") == 0)
    {
        leftright = left_border;
        start_row = atoi(argv[2]);
        start_col = atoi(argv[3]);
        path = left_path;
    }

    int initial_border = start_border(&map, start_row, start_col, leftright);
    if(initial_border == -1)
        return 1;

    find_path(&map, start_row, start_col, initial_border, path);
    
    Map_dtor(&map);
    return 0;
}

Map Map_ctor(int rows, int cols)
{
    Map map;
    map.rows = rows;
    map.cols = cols;
   

    map.cells = malloc(map.rows * map.cols * sizeof(unsigned char));

    return map;
}

void Map_init(Map *map, FILE* fp)
{
    char c = 0;
    for(int i = 0; c != EOF; i++)
    {
        c = fgetc(fp);
        if(c == ' ' || c == '\n' || c == EOF)
        {
            c = fgetc(fp);
            if(c == EOF)
                break;
        }
        map->cells[i] = (c - '0');

    }
    fclose(fp);
}

void Map_dtor(Map *map)
{
  free(map->cells);
}

bool Test_map(Map *map)
{
    bool test = true;
    bool curr_border;
    bool next_border;
    
    for(int curr_row = 0; curr_row < map->rows; curr_row++)
    {
        for(int curr_col = 0; curr_col < map->cols; curr_col++)
        {
            if(curr_row == map->rows - 1 && curr_col == map->cols - 1)
                break;

            // printf("row: %d, col: %d \n", curr_row, curr_col);
            curr_border = isborder(map, curr_row, curr_col, right_border);
            next_border = isborder(map, curr_row, curr_col + 1, left_border);
        
            if(curr_col != map->cols - 1)   
            {
                if(!(curr_border && next_border))
                {
                    if(!(!curr_border && !next_border))
                    {
                        test = false;
                        return test;
                    }
                }   
            }         

            if(curr_row == map->rows - 1)
                break;
            
            curr_border = isborder(map, curr_row, curr_col, third_border);
            next_border = isborder(map, curr_row + 1, curr_col, third_border);
            
            if((curr_row % 2 == 1) && (curr_col % 2 == 0) && curr_row != map->rows - 1)
            {
                if(!(curr_border && next_border))
                {
                    if(!(!curr_border && !next_border))
                    {
                        test = false;
                        return test;
                    }
                }
            } 

            if((curr_row % 2 == 0) && (curr_col % 2 == 1) && curr_row != map->rows - 1)
            {
                if(!(curr_border && next_border))
                {
                    if(!(!curr_border && !next_border))
                    {
                        test = false;
                        return test;
                    }
                }
            }
        }
    }
    
    return test;
}

bool isborder(Map *map, int r, int c, int border)
{
    bool test = true;
    int shared_bits = 0;

    shared_bits = (map->cells[r * map->cols + c]) & border; //c stores bits that exist in both border and target position

    if(shared_bits != border)
    {
        test = false;
    }

    return test;
}

int start_border(Map *map, int r, int c, int leftright)
{

    int side;
    int enter_from = -1; //used to store value of borders i can enter through
    
    enter_from = test_starting_border(map, r, c);
    if(enter_from == -1)
    {
        fprintf(stderr,"trying to enter maze from invalid position\n");
        return -1;
    }

    if(leftright == 2)
    {
        side = follow_right(map, r, c, enter_from);
        if(side == -1)
        {
            return -1;
        }
    }

    if(leftright == 1)
    {
        side = follow_left(map, r, c, enter_from);
        if(side == -1)
        {
            return -1;
        }
    }

    return side;
}

int test_starting_border(Map *map, int r, int c)
{

    int test = 0;

    if(r <= 0 || c <= 0 || r > map->rows || c > map->cols)
    {
        test = -1;
        return test;
    }

    if(!((r == 1 || r == map->rows) || (c == 1 || c == map->cols)))
    {
        test = -1;
        return test;
    }

    if(c == 1 && r == 1)//if entering on left-top corner
    {
        if((isborder(map, r - 1, c - 1, left_border) == true) && (isborder(map, r - 1, c - 1, third_border) == false))
        {
            test = third_border; //can enter from left
            return test;
        }

        if((isborder(map, r - 1, c - 1, left_border) == false) && (isborder(map, r - 1, c - 1, third_border) == true))
        {
            test = left_border; //can enter from top
            return test;
        }

        if((isborder(map, r - 1, c - 1, left_border) == false) && (isborder(map, r - 1, c - 1, third_border) == false))
        {
            test = left_border + third_border; //can enter from top or from left
            return test;
        }

        test = -1;
        return test;
    }

    if(c == 1 && (r != 1 && r != map->rows))//entering from left side and not from corner
    {
        test = left_border; //can enter from left
        if(isborder(map, r - 1, c - 1, left_border))
        {
            test = -1;
            return test;
        }
    }

    if(c == map->cols && (r != 1 && r != map->rows))//entering from right side and not from corner
    {
        test = right_border; //can enter from right
        if(isborder(map, r - 1, c - 1, right_border))
        {
            test = -1;
            return test;
        }
    }

    if(r == 1 && c % 2 == 0) //cant enter maze from top on even col
    {
        test = -1;
        return test;
    }

    if(r == 1 && c != 1 && c != map->cols && c % 2 == 1)//entering from top and not from corner
    {
        test = third_border; //can enter from top
        if(isborder(map, r - 1, c - 1, third_border))
        {
            test = -1;
            return test;
        }
    }

    if(r == map->rows && c != 1 && c != map->cols && ((c % 2 == 0 && r % 2 == 1) || (c % 2 == 1 && r % 2 == 0)))//entering from bottom and not from corner
    {
        test = third_border;
        if(isborder(map, r - 1, c - 1, third_border))
        {
            test = -1;
            return test;
        }
    }

    if(c == map->cols && r == 1)//entering from right-top corner
    {
        if(map->cols % 2 == 0)//if my map has even number of cols i dont have to check top border
        {
            test = right_border;
            
            if(isborder(map, r - 1, c - 1, right_border))
            {
                test = -1;
                return test;
            }
        }else{      
            if((isborder(map, r - 1, c - 1, right_border) == true) && (isborder(map, r - 1, c - 1, third_border) == false))
            {
                test = third_border; //can enter from left
                return test;
            }

            if((isborder(map, r - 1, c - 1, right_border) == false) && (isborder(map, r - 1, c - 1, third_border) == true))
            {
                test = right_border; //can enter from top
                return test;
            }

            if((isborder(map, r - 1, c - 1, left_border) == false) && (isborder(map, r - 1, c - 1, third_border) == false))
            {
                test = right_border + third_border; //can enter from top or from left
                return test;
            }

            test = -1;
            return test;
            
        }
    }

    if(c == map->cols && r == map->rows)//entering from right-bottom corner
    {
        if((map->cols % 2 == 1 && map->rows % 2 == 1) || (map->cols % 2 == 0 && map->rows % 2 == 0))//if my map has odd number of cols i dont have to check bottom border
        {
            test = 2;
            if(isborder(map, r - 1, c - 1, right_border))
            {
                test = -1;
                return test;
            }
        }else{
            if((isborder(map, r - 1, c - 1, right_border) == true) && (isborder(map, r - 1, c - 1, third_border) == false))
            {
                test = third_border; //can enter from left
                return test;
            }

            if((isborder(map, r - 1, c - 1, right_border) == false) && (isborder(map, r - 1, c - 1, third_border) == true))
            {
                test = right_border; //can enter from top
                return test;
            }

            if((isborder(map, r - 1, c - 1, left_border) == false) && (isborder(map, r - 1, c - 1, third_border) == false))
            {
                test = right_border + third_border; //can enter from top or from left
                return test;
            }
            test = -1;
            return test;
        }
    }

    if(c == 1 && r == map->rows)//entering from left-bottom corner
    {
        if(map->rows % 2 == 0)//if my map has even number of rows i dont have to check bottom border
        {
            if((isborder(map, r - 1, c - 1, left_border) == true) && (isborder(map, r - 1, c - 1, third_border) == false))
            {   
               test = third_border; //can enter from bottom
               return test;
            }

            if((isborder(map, r - 1, c - 1, left_border) == false) && (isborder(map, r - 1, c - 1, third_border)== true))
            {
                test = left_border; //can enter from left
                return test;
            }
            
            if((isborder(map, r - 1, c - 1, left_border) == false) && (isborder(map, r - 1, c - 1, third_border) == false))
            {
                test = left_border + third_border; //can enter from bottom or from left
                return test;
            }
    
            test = -1;
            return test;
        }else{
            if(isborder(map, r - 1, c - 1, left_border))
            {
            test = -1;
            return test;
            }else{
                test = left_border;
            }
        }
    }

    return test;
}

int follow_right(Map *map, int r, int c, int enter_from)
{
    int side;

    if(c == 1 && r % 2 == 1 && (enter_from & left_border) == enter_from)
    {
        side = right_border;
        return side;
    }

    if(c == 1 && r % 2 == 0)
    {
        side = third_border;
        return side;
    }

    if(c == map->cols && (enter_from & right_border) == enter_from)
    {
        if((map->cols % 2 == 1 && r % 2 == 1) || (map->cols % 2 == 0 && r % 2 == 0))
        {
            side = third_border;
            return side;
        }
        
        if((map->cols % 2 == 1 && r % 2 == 0) || (map->cols % 2 == 0 && r % 2 == 1))
        {
        side = left_border;
        return side;
        }
    }

    if(r == 1)
    {
        side = left_border;
        return side;
    }

    if(r == map->rows)
    {
        side = right_border;
        return side;
    }

    return -1; //i dont return something before this something isnt right
}

int follow_left(Map *map, int r, int c, int enter_from)
{
    int side;

    if(c == 1 && r % 2 == 1 && (enter_from & left_border) == enter_from) //enter from left on odd row
    {
        side = third_border;
        return side;
    }

    if(c == 1 && r % 2 == 0)//from left
    {
        side = right_border;
        return side;
    }

    if(c == map->cols && (enter_from & right_border) == enter_from) //enter from right
    {
        if((map->cols % 2 == 1 && r % 2 == 1) || (map->cols % 2 == 0 && r % 2 == 0))
        {
            side = left_border;
            return side;
        }
        
        if((map->cols % 2 == 1 && r % 2 == 0) || (map->cols % 2 == 0 && r % 2 == 1))
        {
        side = third_border;
        return side;
        }
    }

    if(r == 1)
    {
        side = right_border;
        return side;
    }

    if(r == map->rows)
    {
        side = left_border;
        return side;
    }

    return -1;
}

int get_triangle_orient(int r, int c)
{
    if((r % 2 == 1 && c % 2 == 1) || (r % 2 == 0 && c % 2 == 0)) //if im on odd row and odd col or even row and even col
    {
        return down;
    }else{
        return up;
    }
}

bool still_inside(Map *map, int r, int c)
{
    if(r > map->rows || r < 1 || c > map->cols || c < 1) //if i have moved past last row/col
    {
        return false;
    }

    return true;
}

void find_path(Map *map, int r, int c, int starting_side, int path)
{
    printf("%d, %d\n", r, c);
    int move_count = get_triangle_orient(r, c);
    int curr_border = starting_side;
    if(!isborder(map, r - 1, c - 1, curr_border)) //initial check to see if i can exit the maze from starting point
    {
        move(&r, &c, curr_border, move_count);
        move_count++;
        if(curr_border == right_border) //if i move to next cell from right i moved there through its left border
        {
            curr_border = left_border;
        }else{
            if(curr_border == left_border)
            {
                curr_border = right_border;
            }
        } 
    }

    while(still_inside(map, r, c))
    {        
        curr_border = next_border(curr_border, move_count, path);
    
        if(!isborder(map, r - 1, c - 1, curr_border)) //check if i can move through suspected border
        {
            printf("%d, %d\n", r, c); //print coordinates
            move(&r, &c, curr_border, move_count);
            move_count++; 

            if(curr_border == right_border)
            {
                curr_border = left_border;
            }else{
                if(curr_border == left_border)
                {
                    curr_border = right_border;
                }
            } 
        }        
    }
    printf("\n");
}

void move(int *r, int *c, int passed_through, int move_count)
{
    if(passed_through == third_border && move_count % 2 == 1) //even move_count means im in upwards facing triangle
    {
        *r = *r + 1;
    }

    if(passed_through == third_border && move_count % 2 == 0) //odd move_count means im in upwards facing triangle
    {
        *r = *r - 1;
    }

    if(passed_through == left_border)
    {
        *c = *c - 1;
    }

    if(passed_through == right_border)
    {
        *c = *c + 1;
    }
}

int next_border(int curr_border, int move_count, int path)
{
    int border = curr_border;

    if(move_count % 2 == path) //if path is odd it means im following left hand and if move_count if odd it means im in upwards triangle
    {
        if(curr_border == third_border) //switching borders depend on what rule i follow
            border = left_border;

        if(curr_border == right_border)
            border = third_border;

        if(curr_border == left_border)
            border = right_border;
    }else{
        if(curr_border == third_border)
            border = right_border;

        if(curr_border == right_border)
            border = left_border;

        if(curr_border == left_border)
            border = third_border;
    }

    return border;
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