#include <iostream>
#include <random>
using namespace std;

//	combine
void Merge(int* arr, int left, int mid, int right, int* arr2)
{
	int index1 = left;
	int index2 = mid+1;
	int* buffer = new int [right - left + 1];
	int* buffer2 = new int [right - left + 1];
	int bufferIndex = 0;
	
	//	combine by selecting a smallest number each time, and copy it into buffer array
	for(bufferIndex = 0; index1 <= mid && index2 <= right; bufferIndex++)
	{
		if(arr[index1] < arr[index2])
		{
			buffer[bufferIndex] = arr[index1];
			buffer2[bufferIndex] = arr2[index1];
			index1++;
		}
		else
		{
			buffer[bufferIndex] = arr[index2];
			buffer2[bufferIndex] = arr2[index2];
			index2++;
		}
	}
	
	//	copy the rest numbers
	while(index1 <= mid)
	{
		buffer[bufferIndex] = arr[index1];
		buffer2[bufferIndex] = arr2[index1];
		index1++;
		bufferIndex++;
	}
	while(index2 <= right)
	{
		buffer[bufferIndex] = arr[index2];
		buffer2[bufferIndex] = arr2[index2];
		index2++;
		bufferIndex++;
	}
	
	//	copy buffer array to sort array
	for(int i = left; i <= right; i++)
	{
		arr[i] = buffer[i-left];
		arr2[i] = buffer2[i-left];
	}

	
	delete [] buffer;
}


//	do merge sorting on arr
//	change the index of element in arr2 accroading to the change of arr
void MergeSort(int* arr, int left, int right, int* arr2)
{
	if(left < right)
	{
		int mid = (left + right) / 2;
		MergeSort(arr, left, mid, arr2);	//	divide
		MergeSort(arr, mid+1, right, arr2);
		Merge(arr, left, mid, right, arr2);
	}
}

//	count inversions
int Merge_and_Count(int* arr, int left, int mid, int right)
{
	int index1 = left;
	int index2 = mid+1;
	const int length = right - left + 1;
	int buffer[length];
	int inversionCount = 0;
	
	int bufferIndex;
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
			inversionCount += mid - index1 + 1;
		}
	}
	
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
	
	for(int i = left; i <= right; i++)
	{
		arr[i] = buffer[i - left];
	}
	
	return inversionCount;
}


//	divide
int Sort_and_Count(int* arr, int left, int right)
{
	if(left >= right)
		return 0;
	else
	{
		int mid = (left + right) / 2;
		int countRight = Sort_and_Count(arr, left, mid);
		int countLeft = Sort_and_Count(arr, mid+1, right);
		int countMerge = Merge_and_Count(arr, left, mid, right);
		return countRight + countLeft + countMerge;		
	}
}


int main()
{
	//	hobby sequence
	const int length = 6;
	int hobby1[length] = {4, 6, 5, 1, 3, 2};
	int hobby2[length] = {6, 1, 2, 4, 3, 5};
	
	//	sort hobby1, and sort hobby2 by the sequence of hobby1
	MergeSort(hobby1, 0, 5, hobby2);
	
	//	output hobby
	cout << "Hobby1: ";
	for(int number : hobby1)
		cout << number << " ";
	cout << '\n';
	
	cout << "Hobby2: ";
	for(int number : hobby2)
		cout << number << " ";
	cout << '\n';
	
	//	count inversion by using merge sort
	//		先將list拆成左右兩個部分
	//		總inversion數 = 左測內部inversion數 + 右側內部inversion數 + 合併時的inversion數
	//		其中「左測內部inversion數」和「右側內部inversion數」又分別為左右部分在先前合併時所得到
	int inversion = Sort_and_Count(hobby2, 0, 5);
	cout << "Inversion: " << inversion << '\n';
	
	return 0;
}
