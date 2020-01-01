#include<string>
#include<algorithm>
#include<iostream>
using std::string;


string toLowerCase(string str) {
	std::transform(std::begin(str), std::end(str), std::begin(str),
		[](auto c) { return std::tolower(c); }
	);

	return str;
}

/*void main()
{
	string input{ "Hello World." };
	string output = toLowerCase(input);

	std::cout << output << std::endl;
}*/