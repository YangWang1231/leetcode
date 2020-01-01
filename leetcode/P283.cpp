#include<vector>
#include<iostream>
#include<algorithm>
using std::cout;
using std::vector;



void moveZeroes(vector<int>& nums) {
	std::stable_partition(std::begin(nums), std::end(nums),
		[](auto e) { return e != 0; });
	//unstable sort, can split nonzero while broken the orders of elements.
	/*std::partition(std::begin(nums), std::end(nums),
		[](auto e) { return e != 0; });*/
}


//void main()
//{
//	vector<int> input{ 0,3,0,5,6,0 };
//	moveZeroes(input);
//
//	for (auto e : input) {
//		cout << e;
//	}
//	cout << std::endl;
//}