#include <stdio.h>

#define N 5000

int main(){

    int a = (N + 4096 - 1) & ~(4096 - 1);
    size_t b = (0.25 * a);
    int c = (0.75 * a);
    printf("%d\n",b);
    printf("%d\n",c);

    return 0;
}
