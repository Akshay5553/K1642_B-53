#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)
volatile int r_t = 0;

pthread_t thread[3]; 

int N_E;

struct Output{
	
	int minimum;
	int maximum;
	int avg;

}Output;


void *findminimum(void *array_ptr){
	
	int i; 
	
	int *elements = (int*)array_ptr; 

	Output.minimum = elements[0]; 

	for(i = 0; i < N_E; i++){	

		if(elements[i] < Output.minimum){	

			Output.minimum = elements[i];	
	
		}
	
	}

	r_t -= 1;	

return NULL;

}


void *findmaximum(void *array_ptr){
	
	int i;	

	int *elements = (int*)array_ptr;  
	
	for(i = 0; i < N_E; i++){	

		if(elements[i] > Output.maximum){	

			Output.maximum = elements[i];

		}
	}

	r_t -= 1;	
return NULL;

}


void *findavg(void *array_ptr){
	
	int i;	 

	int *elements = (int*)array_ptr; 	

	for(i = 0; i < N_E; i++){		

		Output.avg += elements[i];		

	}

	Output.avg = Output.avg/N_E;

	r_t -= 1;	

return NULL;

}


int getArrayInput(int n, int *array_ptr){
		
		int a;

		int numberOfElements = 0;

    	printf("Creating Dynamic Array...\n-\n");

		for(;;){  

    		printf("Enter a positive value:\nNegative Number to Stop\n-\n");
   
    		

			if (scanf("%d",&a) != 1){

				printf("\nOops that wasn't an Integer\nlets try filling the array again\nRemember INTEGERS only!\n");

				exit(EXIT_FAILURE);
			
			}

    		if (a >= 0){ 

       		 	if (numberOfElements == n){

          	  	  n += 1; 
            		
          		  array_ptr = realloc(array_ptr, n * sizeof(int));
            
       			 }

        		array_ptr[numberOfElements++] = a;
    
    		} else {
        
       		 printf("\nNumber of Integers: %d\n", numberOfElements);
       
       		 break;

   				 }

			}

	return numberOfElements;
	
		}

void joinThreads(int numberOfThreads){
	
	int i; 

	int s; 
	while(numberOfThreads >= 0){

		s = pthread_join(thread[numberOfThreads], NULL);

		 
		 if (s != 0){
		 	
			handle_error_en(s, "pthread_create");
		 
		 }

		 numberOfThreads--;

	}
	
}
	

void createThreads(int *array_ptr){
	
	int s; 
 
 	s = pthread_create(&thread[0], NULL, findminimum, (void *)array_ptr);

	 if (s != 0){

			handle_error_en(s, "pthread_create");
		 
		 }
		 	r_t += 1;

	 
	 s = pthread_create(&thread[1], NULL, findmaximum, (void *)array_ptr);

		 if (s != 0){
        
            handle_error_en(s, "pthread_create");
       	
       	 }
        	 r_t += 1;

	
	 s = pthread_create(&thread[2], NULL, findavg, (void *)array_ptr);
	 		 
		 if (s != 0){

           handle_error_en(s, "pthread_create");
       	
       	 }
			
			r_t += 1;

}


int main(){

	int n = 1; 

	int *array_ptr = malloc(n * sizeof(int));
		 N_E = getArrayInput(n, array_ptr);
		
		 createThreads(array_ptr);
		
	    	while(r_t>0){	
	
				sleep(1);

			}

		joinThreads(2);
		printf("\nThe average is %d\nThe maximum is %d\nThe minimum is %d\n",Output.avg, Output.maximum, Output.minimum);

	return(0);

}
