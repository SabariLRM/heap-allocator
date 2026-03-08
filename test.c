#include <stdio.h>
#include <stdlib.h>
#include "my_alloc.h"

int main(int *argc,char **argv){

    heap_init(4096);

    char *a1 = alloc(64);
    char *a2 = alloc(72);

    a1[0] = 'a';
    a1[1] = 'b';

    a2[0] = 'c';
    a2[1] = 'd';

    printf("%c\n",a1[0]);
    printf("%c\n",a2[1]);
    printf("%d\n",atoi(argv[1]));

    freec(a1);
    freec(a2);
    freeh();

    return 0;
}
