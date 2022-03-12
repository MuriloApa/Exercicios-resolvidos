#include <stdio.h>
 
int main() {
 
    int p1, p2, n1, n2;
    float v1, v2;
    scanf("%d %d %f %d %d %f", &p1, &n1, &v1, &p2, &n2, &v2);
    printf("VALOR A PAGAR: R$ %.2f\n", n1*v1+n2*v2);
    return 0;
}
