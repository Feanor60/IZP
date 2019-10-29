#include <stdio.h>
#include <string.h>
 
int main(int argc, char *argv[])
{
  int i;
  int j;
  int found = 0;
  for (i = 1; i < argc && !found; i++)
  {
    for (j = 0; argv[i][j] != '\0' && !found; j++)
      if (argv[i][j] == 'h')
      {
        found = 1;
      }
  }
 
  if (found)
  {
    printf("Pozice argumentu: %d\n", i);
    printf("Pozice znaku h v argumentu: %d\n", j);
    return 0;
  }
  return 1;
}