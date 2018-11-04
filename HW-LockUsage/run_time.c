#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>

typedef struct __counter_t{
	int value;
}counter_t;

void init(counter_t *c){
	c->value = 0;
}

void increment(counter_t *c){
	c->value++;
}

void decrement(counter_t *c){
	c->value--;
}

int get(counter_t *c){
	return c->value;
}

void *mythread(void *c){
	counter_t *t = (counter_t*)c;
	while(t->value <=2000000)
		increment(t);
	return NULL;
}

int main(int argc, char const *argv[]){
	// Get start time
	struct timeval start_t, end_t;
	gettimeofday(&start_t, NULL);

	counter_t counter;
	init(&counter);

	pthread_t p1, p2;
	int rc;
	rc = pthread_create(&p1, NULL, mythread, (void*)&counter); assert(rc == 0);
	rc = pthread_create(&p2, NULL, mythread, (void*)&counter); assert(rc == 0);

	rc = pthread_join(p1, NULL); assert(rc == 0);
	rc = pthread_join(p2, NULL); assert(rc == 0);
	printf("%s\n", "Main end");

	// Get end time
	gettimeofday(&end_t, NULL);
	printf("tv_usec = %ld  :  tv_sec = %ld\n", end_t.tv_usec-start_t.tv_usec, end_t.tv_sec-start_t.tv_sec);	
	return 0;
}