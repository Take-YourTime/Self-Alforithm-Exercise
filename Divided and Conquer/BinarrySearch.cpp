#include <iostream>
using namespace std;

bool binarySearch(int* arr, int left, int right, const int key)
{
	if(left > right)
		return false;
	
	int mid = (left + right) / 2;
	
	if(arr[mid] == key)
		return true;
	else if(arr[mid] > key)
		return binarySearch(arr, left, mid-1, key);
	else
		return binarySearch(arr, mid+1, right, key);
}

int main()
{
	int arr[10] = {0, 2, 4, 5, 7, 10, 11, 12, 14, 17};
	for(int number : arr)
		cout << " " << number;
	cout << '\n';
	
	int key;
	
	while(!cin.eof() && cin >> key)
	{
		cout << (binarySearch(arr, 0, 9, key) ? "found" : "not found") << '\n';
	}
	
	
	return 0;
}
