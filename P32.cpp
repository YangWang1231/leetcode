#include<string>
#include<algorithm>
using namespace std;

string gstring;
int find_longest_parenthese(int index)
{
	if (index >= gstring.length())
		return 0;

	if (gstring[index] == '(' && gstring[index + 1] == ')') {
		return 2 + find_longest_parenthese(index + 2);
	}
	else if (gstring[index] == '(' && gstring[index + 1] == '(') {
		int result = find_longest_parenthese(index + 1);
		if (result == 0) {
			return 0;
		}
		else {
			if (gstring[index + result + 1] == ')') {
				return 2 + result + find_longest_parenthese(index + result + 2);
			}
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
		{//�ӵ�ǰ�ַ���ʼ������well formatted
			i++;
		}
		else {
			i += k;
			max_length = max(max_length, k);
		}
	}

	return max_length;
}

void main()
{
	int result = longestValidParentheses("((()))())");
}