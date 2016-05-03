#include <iostream>
#include <cstdio>
#include <cstdlib>

void merge_two_array(int* arr, int left, int mid, int right)
{
	int front = left;
	int rear = mid+1;
	int sIdx = left;

	// Allocate temporary memory for sorting
	int* sortArr = (int*)malloc(sizeof(int)*(right+1));

	// Copy values to sortArr
	while(front <= mid && rear <= right) {
		if(arr[front] < arr[rear])
			sortArr[sIdx++] = arr[front++];
		else
			sortArr[sIdx++] = arr[rear++];
	}

	// Copy the rest of values not copied
	if(front > mid) {
		for(int i=rear; i<=right; i++, sIdx++)
			sortArr[sIdx] = arr[i];
	}

	// Copy the rest of values not copied
	if(rear > right) {
		for(int i=front; i<=mid; i++, sIdx++)
			sortArr[sIdx] = arr[i];
	}

	// Copy values in sortArr to original array
	for(int i=left; i<=right; i++) {
		arr[i] = sortArr[i];
	}

	// Free temporarily allocated array
	free(sortArr);
}

void merge_sort(int* arr, int left, int right)
{
	int mid;

	if(left < right) {
		mid = (left+right)/2;
		merge_sort(arr, left, mid);
		merge_sort(arr, mid+1, right);

		merge_two_array(arr, left, mid, right);
	}
}

void print_array(int* arr, int size)
{
	for(int i=0; i<size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main(int argc, char* argv[])
{

	int arr[] = {5,2,3,4,6,1};
	int size = sizeof(arr) / sizeof(int);
	printf("size of arr: %d\n", size);

	printf("Before sort : ");
	print_array(arr, size);
	merge_sort(arr, 0, size);
	printf("After sort  : ");
	print_array(arr, size);
}