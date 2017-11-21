#include<stdio.h>
#define max 100

int main()
{
   int a[max],b,i,sum=0;
   float avg;
   FILE *f1;

   printf("\t\t\t\aAverage calculator\n\n");
   f1=fopen("tot.debagnik","rb");
   fread(&b,sizeof(b),1,f1);
   fclose(f1);
   
   f1=fopen("dat.debagnik","r");
   printf("Data are:\n");
   for(i=1;i<b;i++)
   {
      fscanf(f1,"%d\n",&a[i]);
      printf("Element no. %d is %d",i,a[i]);
   }
   fclose(f1);

   for(i=1;i<b;i++)
   {
      sum=sum+a[i];
   }

   avg=(sum*1.0)/b;
   
   printf("average=\t%f",avg);
   
   f1=fopen("avg.debagnik","w");
   fprintf(f1,"The average of the data is\t%f",avg);
   fclose(f1);

   return 0;
}
