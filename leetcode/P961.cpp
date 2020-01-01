#include<vector>
#include<iostream>
#include<algorithm>
using std::cout;
using std::vector;
using std::endl;


int repeatedNTimes(vector<int>& A) {
	std::sort(std::begin(A), std::end(A));
	auto i = std::adjacent_find(std::begin(A), std::end(A));
	return *i;
}

//void main()
//{
//	vector<int> input{ 5,1,5,2,5,3,5,4 };
//	int repeatval = repeatedNTimes(input);
//
//	cout << "repeat val is:" << repeatval;
//}