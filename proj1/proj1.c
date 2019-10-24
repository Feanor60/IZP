#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char sez_input[100];
    
    if(argc==2)
    {
        fgets(sez_input, 100, stdin)
        
        
    }
    printf("uh oh: %s\n", sez_input);
    printf("uh ohh: %s\n", argv[1]);
    printf("uh ohhh: %d\n",argc);

    return 0;
}