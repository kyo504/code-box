#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_callback1(void *arg);
void *thread_callback2(void *arg);

int main(int argc, char** argv)
{
	int state;
	pthread_t t_id1, t_id2;
	void *t_return;

	state = pthread_create(&t_id1, NULL, thread_callback1, NULL);
	if(state != 0) {
		puts("Failed to create thread...\n");
		exit(1);
	}

	state = pthread_join(t_id1, &t_return);
	if(state != 0) {
		puts("Failed to join...\b");
		exit(1);
	}

	int* sum = (int*)malloc(sizeof(int));
	*sum = *((int*)t_return);

	free(t_return);
	state = pthread_create(&t_id2, NULL, thread_callback2, (void*)sum);
	if(state != 0) {
		puts("Failed to create thread...\n");
		exit(1);
	}

	state = pthread_join(t_id2, &t_return);
	if(state != 0) {
		puts("Failed to join...\n");
		exit(1);
	}

	*sum = *((int*)t_return);

	printf("Sum is %d \n", *sum);

	puts("main funtion is closed...");

	return 0;
}

void *thread_callback1(void *arg)
{
	printf("Thread1 starts...\n");

	int i;
	int* sum = (int*)malloc(sizeof(int));
	for(i=1; i<=5; i++) {
		*sum += i;
		printf("[Thread1] sum = %d\n", *sum);
	}

	return sum;
}

void *thread_callback2(void *arg)
{
	printf("Thread2 starts...\n");

	int i;
	int* sum = (int*)malloc(sizeof(int));

	*sum=*((int*)arg);

	for(i=6; i<=10; i++) {
		*sum += i;
		printf("[Thread2] sum = %d\n", *sum);
	}
	
	return sum;
}
