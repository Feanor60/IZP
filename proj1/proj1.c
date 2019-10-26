#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char seznam_input[100];
    //string to store stdin
    char compare_char_stdin;
    //char to compare parameters with
    char compare_char_param;
    //char to compare stdin with
    char search_parameters[100];
    search_parameters = argv[1];

    if(argc==2)
    //checking for appropriate amount of parameters
    {
        while(fgets(seznam_input,100,stdin)!=NULL)
        //running as long as fgets reads from seznam.txt
       {
            unsigned int pos_char = 0;
            //position of char comparing
            compare_char_stdin = seznam_input[pos_char];
            compare_char_param = search_parameters[pos_char];

            if(strstr(compare_char_stdin,compare_char_param))
            {
                if(strstr())
            }
       }
    }

    fgets(seznam_input,100,stdin);
    compare_char = seznam_input[0];
    
    printf("prvni znak seznam.txt: %c\n", compare_char);
    printf("output seznam.txt: %s\n", seznam_input);
    printf("output argumentu pro hledani: %s\n", argv[1]);
    printf("pocet argumentu: %d\n",argc);

    return 0;
}