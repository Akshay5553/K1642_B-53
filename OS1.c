#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<pthread.h>
int a[30];
int sizeOfArray;
//function for Avg 

//function for  Max
void max(int a[])
{
sleep(1);
 int i,j,temp;
 for(i=0;i<sizeOfArray;i++)
 {
  for(j=0;j<sizeOfArray-i-1;j++)
  {
    if(a[j+1]<a[j])
    {
       temp= a[j];
       a[j]=a[j+1];
       a[j+1]=temp;
    }
  }
 }
 printf("\nThe maximum value is %d ", a[sizeOfArray-1]);
}

//function for Min
void min(int a[])
{
sleep(1);

 int i,j,temp;
 for(i=0;i<sizeOfArray;i++)
 {
  for(j=0;j<sizeOfArray-i-1;j++)
  {
    if(a[j+1]<a[j])
    {
       temp= a[j];
       a[j]=a[j+1];
       a[j+1]=temp;
    }
  }
 }
 printf("\nThe minimum value is %d", a[0]);
}
void avg(int a[])
{
 int i,sum=0,avg;
 for(i=0;i<sizeOfArray;i++)
 {
  sum=sum+a[i];
 }
 avg = sum/sizeOfArray;
 printf("The Average value is %d",avg);
}
//main
void main()
{
 int n,i;
 pthread_t th1,th2,th3;
 printf("Enter size of array and should be less than 30:");
 scanf("%d",&n);
 for(i=0;i<n;i++)
 {
 scanf("%d",&a[i]);
 }
 sizeOfArray = n;
 pthread_create(&th1,NULL,avg,&a);
 pthread_create(&th2,NULL,max,&a);
 pthread_create(&th3,NULL,min,&a);
 pthread_join(th1,NULL);
 pthread_join(th2,NULL);
 pthread_join(th3,NULL);
}
