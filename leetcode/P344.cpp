#include<vector>
#include<iostream>
using std::vector;


void reverseString(vector<char>& s) {
	std::reverse(s.begin(), s.end());
}

//void main()
//{
//	vector<char> input = { 'h', 'e', 'l', 'l', 'o' };
//	reverseString(input);
//	for (auto e : input) {
//		std::cout << e;
//	}
//	std::cout << std::endl;
//
//}