#include <iostream>
#include <pthread.h>
#include <unistd.h>

void *threadFunction (void *value){
	int *x = (int *)value;
	while(*x < 5){
		usleep(10);
		(*x)++;
	}
	return x;
}

int main(){
	int x=0, y=0;
	pthread_t thread;
	
	if(pthread_create(&thread, NULL, &threadFunction, &x) != 0){
		std::cout << "Failed to create the thread\n";
		return 1;
	}
	
	while(y < 5){
		std::cout << "The value of x = " << x << " and y = " << y++ << "\n";
		usleep(10);
	}
	void *result;
	pthread_join(thread, &result);
	int *z = (int *) result;
	std::cout << "Final: x = " << x << ", y = " << y << " and z = " << *z << "\n";
	return 0;
}
