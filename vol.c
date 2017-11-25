#include<stdio.h>

#include<string.h>

int main()
{
   char a[100],*p;
   int n=0,v=0,c=0;
   
   printf("Enter the string");
   gets(a);
   s=a;
   while(*p!='\0')
   {
       if(p=='a'||p=='e'||p=='i'||p=='o'||p=='u')
       {v++;}
       else
       {c++;}
       if(p==' ')
       {n++;}
   }
   printf("%d ,%d, %d,",v,c,n);

   return 0;
}
