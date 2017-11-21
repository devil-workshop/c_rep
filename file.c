#include<stdio.h>
#define max 100
int main()
{
   int a[max],b,i;
   FILE *f1;
   printf("Enter the number of data to calculate\t");
   scanf("%d",&b);
   f1=fopen("tot.debagnik","wb");
   fwrite(&b,sizeof(b),1,f1);
   fclose(f1);
   f1=fopen("dat.debagnik","w");
   for(i=1;i<b;i++)
   {
      printf("Enter element no. %d\t\a",i);
      scanf("%d",&a[i]);
      fprintf(f1,"%d\n",a[i]);
   }
   fclose(f1);
   return 0;
}
