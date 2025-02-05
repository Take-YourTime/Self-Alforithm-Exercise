#include <iostream>
#include <random>
using namespace std;

//	combine
void Merge(int* arr, int left, int mid, int right)
{
	int index1 = left;
	int index2 = mid+1;
	int* buffer = new int [right - left + 1];
	int bufferIndex = 0;
	
	//	combine by selecting a smallest number each time, and copy it into buffer array
	for(bufferIndex = 0; index1 <= mid && index2 <= right; bufferIndex++)
	{
		if(arr[index1] < arr[index2])
		{
			buffer[bufferIndex] = arr[index1];
			index1++;
		}
		else
		{
			buffer[bufferIndex] = arr[index2];
			index2++;
		}
	}
	
	//	copy the rest numbers
	while(index1 <= mid)
	{
		buffer[bufferIndex] = arr[index1];
		index1++;
		bufferIndex++;
	}
	while(index2 <= right)
	{
		buffer[bufferIndex] = arr[index2];
		index2++;
		bufferIndex++;
	}
	
	//	copy buffer array to sort array
	for(int i = left; i <= right; i++)
		arr[i] = buffer[i-left];
	
	delete [] buffer;
}


//	merge sort
void MergeSort(int* arr, int left, int right)
{
	if(left < right)
	{
		int mid = (left + right) / 2;
		MergeSort(arr, left, mid);	//	divide
		MergeSort(arr, mid+1, right);
		Merge(arr, left, mid, right);
	}
}


int main()
{
	//	建立隨機數生成器
	std::random_device rd;	// 真實隨機數來源（硬體），作為種子
	std::mt19937 gen(rd());	// Mersenne Twister 引擎

	//	設定亂數範圍: 1 ~ City數量
	std::uniform_int_distribution<> distrib(0, 200);
	
	int arr[100] = {0};
	for(int i = 0; i < 100; i++)	//	分配隨機亂數
		arr[i] = distrib(gen);
	
	
	cout << "Before sort: ";
	for(int number : arr)
		cout << number << " ";
	cout << "\n\n";
	
	MergeSort(arr, 0, 100-1);	//	sorting by merge sort
	
	cout << "After sort: ";
	for(int number : arr)
		cout << number << " ";
	cout << '\n';
	
	return 0;
}
