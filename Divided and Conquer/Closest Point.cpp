#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Point {
public:
	Point() = default;
	Point(int a, int b)
	{
		x = a;
		y = b;
	}

	void operator = (const Point& another);

	int x;	//	↓
	int y;	//	→
};

void Point::operator = (const Point& another)
{
	this->x = another.x;
	this->y = another.y;
}

//	get the distance of two points
double getDistance(Point p1, Point p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

//	the line segment between two Points
class Line {
public:
	Line() = default;
	Line(Point& p1, Point& p2)
	{
		this->a = p1;
		this->b = p2;
		length = getDistance(p1, p2);
	}
	void operator = (const Line& another);
	
	Point a;
	Point b;
	double length;
};

void Line::operator = (const Line& another)
{
	this->a = another.a;
	this->b = another.b;
	this->length = another.length;
}

//	map size
const int width = 7200;
const int height = 10800;

const int numberOfPoints = 200;	//	number of points


bool cmp(Point a, Point b)
{
	//	small to big
	return a.y < b.y;
}

bool cmp_by_x(Point a, Point b)
{
	return a.x < b.x;
}

//	find the shortest distance of three lines
Line shortest_distance(Line& line1, Line& line2, Line& line3)
{
	Line shortest = line1.length < line2.length ? line1 : line2;
	shortest = line3.length < shortest.length ? line3 : shortest;
	return shortest;
}

//	combine left part and right part
void combine(vector<Point>& list, int left, int mid, int right, Line& min_line)
{
	//	"dis" is the shortest distance of left part and right part
	//	we only need to find the points that are within "dis" distance of the mid point
	vector<Point> mid_points;
	int index = left;
	double dis = min_line.length;
	
	while (index <= right && abs(list[mid].y - list[index].y) >= dis)	//	find the left bound of middle part
		index++;
	while (index <= right && abs(list[mid].y - list[index].y) < dis)	//	insert the point until reach the right bound
	{
		mid_points.push_back(list[index]);
		index++;
	}
	
	if(mid_points.size() <= 1)	//	no point or only one point at the middle part
		return;
	
	for(int i = 0; i < mid_points.size()-1; i++)
	{
		for(int j = i+1; j < mid_points.size(); j++)
		{
			if(abs(mid_points[i].x - mid_points[j].x) < dis && getDistance(mid_points[i], mid_points[j]) < dis)	//	detect the distance of x coordinates is smaller than "dis" first
			{
				dis = getDistance(mid_points[i], mid_points[j]);
				min_line.length = dis;
				min_line.a = mid_points[i];
				min_line.b = mid_points[j];
			}
		}
	}
}

//	use merge sort template to find the closest point
Line split(vector<Point>& list, int left, int right)
{
	//cout << "Split: " << left << " " << right << "\n";
	//	小於三點，直接求出最短的線段
	if (right - left < 3)
	{
		Line line(list[left], list[right]);

		if (right - left == 2)
		{
			if (getDistance(list[left], list[left+1]) < line.length)
				line = Line(list[left], list[left+1]);
			if (getDistance(list[left+1], list[right]) < line.length)
				line = Line(list[left+1], list[right]);
		}
		return line;
	}
	else
	{
		int mid = (left + right) / 2;
		Line left_min_line = split(list, left, mid);
		Line right_min_line = split(list, mid + 1, right);
		Line min_line = left_min_line.length < right_min_line.length ? left_min_line : right_min_line;	//	the mininal line of current part
		//cout << "Before combine: left " << left_min_line.length << " right " << right_min_line.length << " min " << min_line.length << '\n'; 
		combine(list, left, mid, right, min_line);
		//cout << "After combine: " << left << " " << right << " " << min_line.length << "\n";
		return min_line;
	}
}


int main()
{
	//	random engin
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib_width(0, width);
	std::uniform_int_distribution<> distrib_height(0, height);

	vector<Point> list;	//	list of points

	//	insert random points
	for (int i = 0; i < numberOfPoints; i++)
	{
		list.push_back(Point(distrib_height(gen), distrib_width(gen)));
	}

	sort(list.begin(), list.end(), cmp);	// sort the Points into assending order accroading to their y-coordinate
	
	/*
	cout << "[Point List]\n";
	for(int i = 0; i < numberOfPoints; i++)
		cout << i << " " << list[i].y << " " << list[i].x << "\n";
	cout << "\n";
	*/
	
	Line closetPair = split(list, 0, list.size() - 1);	//	get the closest point pair
	
	//	output
	cout << "\n[Final Result]\n";
	cout << "Point1: x↓ " << closetPair.a.x << " y→ " << closetPair.a.y << '\n';
	cout << "Point2: x↓ " << closetPair.b.x << " y→ " << closetPair.b.y << '\n';
	cout << "Distance: " << closetPair.length << endl;
	
	
	double min = 200000000.0;
	int p1, p2;
	for(int i = 0; i < list.size()-1; i++)
	{
		for(int j = i+1; j < list.size(); j++)
		{
			if(getDistance(list[i], list[j]) < min)
			{
				min = getDistance(list[i], list[j]);
				p1 = i; p2 = j;
			}
		}
	}
	cout << "\n[暴力解]\n";
	cout << p1 << " " << p2 << " " << min << '\n';
	return 0;
}
