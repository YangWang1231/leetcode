#include<vector>
#include<iostream>
#include<algorithm>
using std::cout;
using std::vector;
using std::endl;

vector<int> sortedSquares(vector<int>& A) {
	std::transform(std::begin(A), std::end(A), std::begin(A),
		[](auto e) {return e * e; });

	std::sort(std::begin(A), std::end(A));
	return std::move(A);
}

//void main()
//{
//	vector<int> input{ -4,-1,0,3,10 };
//	input = sortedSquares(input);
//	for (auto e : input) {
//		cout << " " << e;
//	}
//}
