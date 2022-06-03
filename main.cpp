////////////////////////////////////////////////////////////////
//							        // 		
//  This is the main.cpp program to estimate the PI value    //
//                                                          //                      
/////////////////////////////////////////////////////////////      


#include <iostream>
#include <time.h>
#include <cstdlib>
#include <pthread.h>
#include "common.h"

using namespace std;

#define NUM_THREADS   8
#define NUM_POINTS    1e9

// See below the call from the file helpers.cpp of the functions which generate random values and to check if a point is inside a circle. 

double generate_random_double();
bool in_circle(double x, double y);

struct thread_data {
    int thread_id;
    int startI;
};

void *PI_Calculation(void* threadarg); 

int circle_count = 0;

int main()   {

   pthread_t threads[NUM_THREADS];
   struct thread_data data[NUM_THREADS];
   pthread_attr_t attr;
   
   long counter = NUM_POINTS/NUM_THREADS;
   int rc;
   int i;
   void* status;
   
   // init the attr
   pthread_attr_init(&attr);
   // configure the attribute in order to have joinable threads
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   
    for( i = 0; i < NUM_THREADS; i++ ) {
      
        data[i].thread_id = i;
        data[i].startI = i*counter;
       
        
        
        rc = pthread_create(&threads[i], &attr, PI_Calculation, (void *)&data[i]);

        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }

	
// free the memory space used by attr variable
    pthread_attr_destroy(&attr);
    for(i=0;i<NUM_THREADS;i++) {

    rc = pthread_join(threads[i], &status);
    
    // rc = 0; it is success
        if (rc != 0) { // not success
           cout << "Error:Cannot join the thread, " << rc << endl;
           


 exit(-1);
}

	cout << "main(): thread " << i << " completed ";
        cout << "with the status " << status << endl;
}
	
	cout <<"The total number of points in the circle is"<<":"<<circle_count<<endl;
	cout.precision(20);
	double PI = 4.0 * (long) circle_count / NUM_POINTS ;  // The method to calculate the estimation value of PI = 3,141592653589793
	cout << "The estimate value of PI is = " << PI << endl; // Display the estimate value of PI in our case 
	
	
pthread_exit(NULL);
  
} 


 

    
 
