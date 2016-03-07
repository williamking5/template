#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std;

int main()
{
    srand((unsigned)time(NULL));

    FILE *fp=fopen("shiyan.in","w");
    fprintf(fp,"100000\n");
    for (int i=0;i<100000;i++){
        fprintf(fp,"%d ",1);
        fprintf(fp,"%d\n",i);
    }
    fclose(fp);
    return 0;
}
