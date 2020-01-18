#include<vector>
#include<iostream>
#include<algorithm>
using std::cout;
using std::vector;
using std::endl;

int search(vector<int>& nums, int target) {
	auto f = std::begin(nums);
	auto l = std::end(nums);
	//auto p = std::is_sorted_until(f, l);
	//run faster than std::is_sorted_until, is log-n
	auto p = std::partition_point(f, l,
		[x = *f](auto e) {return e >= x; });
	if ((target >= * f) && std::binary_search(f, p, target)) {
		auto i = std::lower_bound(f, p, target);
		return std::distance(f, i);
	}
	else if(std::binary_search(p, l, target))
	{
		auto i = std::lower_bound(p, l, target);
		return std::distance(f, i);
	}

	return -1;
}

//void main()
//{
//	int target = 1;
//	vector<int> input{ 1 };
//
//	int index = search(input, target);
//
//	cout << index;
//}