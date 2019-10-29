#include <stdio.h>
int main()
{
    int pocet;
    scanf("%d", &pocet);
    printf("Hodnota je %d\n", pocet);

    float vzdalenost;
    scanf("%f", &vzdalenost);
    printf("Hodnota je %g\n", vzdalenost);

    char znak;
    scanf(" %c", &znak);
    printf("Znak je %c\n", znak);

    char krestni[10];
    scanf("%9s", krestni);

    char prijmeni[10];
    scanf("%9s", prijmeni);

    printf("Jmeno: %s %s\n", krestni, prijmeni);

    return 0;
}
