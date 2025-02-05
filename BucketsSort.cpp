#include <iostream>
#include <ctime>
#include <cmath>
#include <cfloat>
#include <vector>
#include <algorithm>
using namespace std;

const int BUCKETS_NUMBER = 100;				//	how many buckets are used for sorting
const long long int DataNumber = 3000;	//	how many data are there to be sort

/*
	時間複雜度
	最佳情況： O(n+k)，其中 k 是桶的數量。
	平均情況：O(n+k)，其中 k 是桶的數量。
	最差情況：O(n²)
*/

void BucketsSort(vector<double>& number, double min, double max)
{
	vector< vector<double> > buckets(BUCKETS_NUMBER, vector<double>());
	
	//	put all number into buckets
	for(double n : number)
	{
		buckets[(long long int)(n * BUCKETS_NUMBER)].push_back(n);
	}
	
	//	sorting each bucket
	for(int i = 0, index = 0; i < buckets.size(); i++)
	{
		sort(buckets[i].begin(), buckets[i].end());
		
		//	copy buckets back to list
		for(double n : buckets[i])
		{
			number[index] = n;
			index++;
		}
	}
	
	//for(int i = 0; i < buckets.size(); i++)
		//cout << i << " " << buckets[i].size() << '\n';
}

int main()
{
	srand(time(NULL));
	
	vector<double> number;	//	number list
	
	double min = DBL_MAX, max = DBL_MIN;
	double buffer;
	
	//	create random floating number, and record the max number and the min number
	for(long long int i = 0; i < DataNumber; i++)
	{
		buffer = (double)(rand() % 10000) / 10000.0;
		number.push_back(buffer);
		
		if(buffer > max)
			max = buffer;
		if(buffer < min)
			min = buffer;
	}
	
	cout << "min " << min << " max " << max << '\n';
	
	cout << "buckets sort\n";
	BucketsSort(number, min, max);
	for(double n : number)
		cout << n << " \n";
	
	cout << "\n\n";
	cout << "finish\n";
	
	return 0;
}
