#include <stdio.h>
 
int main() {
 
    char nome[20];
    double fixo, montante;
    scanf("%s %lf %lf", nome, &fixo, &montante);
    printf("TOTAL = R$ %.2lf\n", fixo+montante*0.15);
    return 0;
}
