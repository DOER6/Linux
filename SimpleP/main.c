#include <stdio.h>
#include "add.h"
int main()
{
int rel =0,j=20;
int k=30;
for (int i =0;i < k;i++)
{
rel = add( i,k);
printf("hello Linux,i+k =%d\n", rel);
}
return 0;
}


