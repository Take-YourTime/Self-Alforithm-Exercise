#include <iostream>
using namespace std;

//	adjust max heap (檢查root有沒有比左右子樹的root大)
void maxHeapify(int* arr, int i, int size)
{
	//	out of array size
	if(i >= size)
		return;
	
	//	the index of left child and right child
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	
	//	the index of largest node
	int largest = i;
	
	//	find the largest node
	if(left < size && arr[left] > arr[largest])
		largest = left;
	if(right < size && arr[right] > arr[largest])
		largest = right;
	
	//	數or子樹的root不是最大值時，才需對調並繼續往下檢查
	if(largest != i)
	{
		swap(arr[i], arr[largest]);
		maxHeapify(arr, largest, size);
	}
}

//	從陣列末端運行heap sort
void buildMaxHeap(int* arr, int size)
{
	for(int i = size - 1; i >= 0; i--)
	{
		maxHeapify(arr, i, size);
	}
}

//	max heap
void maxHeap(int* arr, int size)
{
	//	將tree變成max heap tree
	buildMaxHeap(arr, size);
	
	//	開始sorting
	while(size > 0)
	{
		//	root此時為最大值，將root與末段節點對調，並將array帶排序的size-1
		swap(arr[0], arr[size-1]);
		size--;
		maxHeapify(arr, 0, size);
	}
}
int main()
{
	int arr[] = {4, 10, 3, 5, 1, 9};
	int size = sizeof(arr) / sizeof(arr[0]);
	
	//	sorting
	maxHeap(arr, size);
	
	//	output result
	for(int number : arr)
		cout << number << " ";
	cout << '\n';
	return 0;
}
