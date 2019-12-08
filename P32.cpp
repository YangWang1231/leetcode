#include<string>
#include<algorithm>
#include<utility>
using namespace std;

string gstring;
bool first_find = true;
int first_pos = 0;

int find_longest_parenthese(int index)
{
	if (index >= gstring.length())
		return 0;


	if (gstring[index] == '(' && gstring[index + 1] == ')') {
		if (first_find == true) {
			first_find = false;
			first_pos = index;
		}
		return 2 + find_longest_parenthese(index + 2);
	}
	else if (gstring[index] == '(' && gstring[index + 1] == '(') {
		int result = find_longest_parenthese(index + 1);
		if (result == 0 || (index + result) == (gstring.length() - 1)) {
			return 0;
		}
		else {
			if (first_find == true) {
				first_find = false;
				first_pos = index;
			}
			if (gstring[index + result + 1] == ')') {
				return 2 + result + find_longest_parenthese(index + result + 2);
			}
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

int longestValidParentheses(string s) {
	gstring = s;
	int max_length = 0;
	for (int i = 0; i < s.length(); ) {
		int k = find_longest_parenthese(i);
		if (k == 0)
		{//从当前字符开始，不是well formatted
			//i++; //每次推进1 太慢了
			if (first_pos == 0){
				i++;
			}
			else {
				i = first_pos;
				first_pos = 0;
			}
		}
		else {
			i += k;
			max_length = max(max_length, k);
		}
	}

	return max_length;

}

//void main()
//{
//	int result = longestValidParentheses(")(((((()())()()))()(()))(");
//}