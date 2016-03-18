#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_summation(void *arg);

//int sum=0;
int sum1[] = {1, 5};
int sum2[] = {6, 10};

int main(int argc, char** argv)
{
	pthread_t id_t1, id_t2;
	void* t_return;

	int* sum = (int*)malloc(sizeof(int));

	pthread_create(&id_t1, NULL, thread_summation, (void *)sum1);
	pthread_create(&id_t2, NULL, thread_summation, (void *)sum2);

	pthread_join(id_t1, &t_return);

	*sum = *((int*)t_return);
	free(t_return);

	pthread_join(id_t2, &t_return);
	*sum += *((int*)t_return);
	free(t_return);

	printf("Sum is %d \n", *sum);

	return 0;
}

void *thread_summation(void *arg)
{
	int start = ((int*)arg)[0];
	int end = ((int*)arg)[1];

	int* sum = (int*)malloc(sizeof(int));

	for( ; start<=end; start++ ) {
		*sum += start;
	}

	return sum;
}
