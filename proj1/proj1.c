#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char sez_input[100];
    printf("Hello world!\n");
     
    fgets(sez_input, 100, stdin);

    printf("%s", sez_input);
    printf("%s", argv[1]);
    return 0;
}