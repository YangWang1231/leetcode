#include<vector>
#include<iostream>
#include<algorithm>
using std::cout;
using std::vector;

vector<int> sortArrayByParity(vector<int>& A) {
	std::partition(std::begin(A), std::end(A),
		[](auto e) {return e % 2 == 0; });
	return A;
}

//void main()
//{
//	vector<int> input{ 1,3,4,5,6 };
//	vector<int> output = sortArrayByParity(input);
//
//	for (auto e : output) {
//		cout << e;
//	}
//	cout << std::endl;
//}