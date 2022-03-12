#include <stdio.h>
 
int main() {
 
    int func, horas;
    float valor;
    scanf("%d %d %f", &func, &horas, &valor);
    printf("NUMBER = %d\nSALARY = U$ %.2f\n", func, horas*valor);
    return 0;
}
