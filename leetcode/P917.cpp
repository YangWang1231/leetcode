#include<vector>
#include<iostream>
#include<algorithm>
#include<string>
using std::string;
using std::cout;
using std::vector;
using std::endl;

string reverseOnlyLetters(string S) {
	std::partition(std::begin(S), std::end(S),
		[b = true](auto e)mutable{
		if (::isalpha(e)) {
			b = !b;
		}
		return b;
	});
	return S;
}

//void main()
//{
//	string input{ "~Test1ng-Leet=code-Q!" };
//	string output = reverseOnlyLetters(input);
//	cout << output;
//}