//dynamic memory allocation for a matrix

#include<stdio.h>
#include<stdlib.h>

int main()
{
   int **m,row,col,i,j;
   printf("Enter number of rows in a matrix:\t");
   scanf("%d",&row);
   printf("Enter number of column in a matrix:\t");
   scanf("%d",&col);
   
   m=(int**)malloc(row*sizeof(int*));
   
   for(i=0;i<row;i++)
   {
      *(m+i)= (int*)malloc(col*sizeof(int));
   }

   for(i=0;i<row;i++)
   {
      for(j=0;j<col;j++)
      {
         printf("Enter the element [%d]-[%d]:\t\a",i,j);
         scanf("%d",(*(m+i)+j));
      }
   }

   for(i=0;i<row;i++)
   {
      for(j=0;j<col;j++)
      {
         printf("%d\t",*(*(m+i)+j) );
         if(j==col)
         {
            printf("\n");
         }
      }
   }
   return 0;
}
