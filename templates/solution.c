#include <stdio.h>
#include <stdlib.h>

int main(){

        int i;
        int n, k;
        char woord[100];

        scanf("%d\n", &n);
        for(i=0; i < n; i++){
                scanf("%d %s\n", &k, woord);

                printf("%c\n", woord[k-1]);
        }

        return 0;
}