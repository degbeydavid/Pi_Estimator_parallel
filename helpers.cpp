////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
//                                                                                    //
// This is helpers.cpp program that contains the method to generate the random values //
// and the one to check if a point is inside a circle.                                //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////


#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <pthread.h>
#include "common.h"

#define NUM_THREADS   8
#define NUM_POINTS    1e9

using namespace std;

// The function below allow to generate random values

double generate_random_double() {
    double rn = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    return rn;
}

bool in_circle(double x, double y) {
    double d = sqrt((x * x) + (y * y));
    if (d <= 1.0) {
        return true;
    }
    return false;
    // return d <= 1.0
}





struct thread_data {
    int thread_id;
    int startI;
};


// The PI_Calculation function allows to check if a point is inside a circle. 	
	
void *PI_Calculation(void* threadarg) {
	struct thread_data *my_data;
    	my_data = (struct thread_data *) threadarg;
	
	int counter = NUM_POINTS/NUM_THREADS;
	int circle_count_per_thread = 0;
	int start = my_data->startI;
	
	int end = start + counter; 
	
        for (int i = start; i < end; i++) { 
	
        	double x = generate_random_double();
        	double y = generate_random_double();
       		if (in_circle(x, y)) {
       		
       		circle_count_per_thread++;
       	
            	}
            	
            	
            }        	

	cout << "The circle_count value of the Thread with ID = " <<my_data->thread_id << " is : " << circle_count_per_thread<< endl; // Display the circle count value of each thread
	
	circle_count += circle_count_per_thread; // Incrementation of the total number of points inside the circle
	
	
    	pthread_exit(NULL);
    	
}  	
