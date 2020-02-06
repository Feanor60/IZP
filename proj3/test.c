#include <stdio.h>
#include <math.h>


int main()
{
    unsigned int a = 7; // 0111
    int b = 4; // 0100
    int c = 0;
    int powered = 0;

    powered = pow(2,0);

    for(int r = 1; r < 5; r++)
    {        
        printf("r: %d\n", r);

        if( r + 1 > 7)
        {
            break;
        }
    }

    c = a & b;
    printf("c: %d\npowered: %d\n", c, powered);   

    return 0;
}