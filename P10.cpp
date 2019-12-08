/*
recrusive solution for regression string matching.
*/

#include<vector>
#include<string>
using namespace std;

typedef vector<vector<bool>> metrix;

metrix g_memo;

void init_metrix(int row, int col)
{
	g_memo.resize(row);
	for (auto row_vec : g_memo) {
		row_vec.resize(col);
	}
}

bool match_str(int i, int j, const string& s, const string& p)
{
	if (j >= p.length()){
		return i >= s.length();
	}
	
	bool firstmatch = (i < s.length()) && ( (s[i] == p[j]) || (p[j] == '.'));
	if (j + 1 < p.length() && p[j + 1] == '*') {
		return match_str(i, j + 2, s, p) || (firstmatch && match_str(i + 1, j, s, p));
	}
	else {
		return firstmatch && match_str(i + 1, j + 1, s, p);
	}
}

bool isMatch(string s, string p) 
{
	init_metrix(s.length(), p.length());
	return match_str(0,0, s, p);
}

string s = "ab";
string p = ".*c";

//void main()
//{
//	bool result = isMatch(s, p);
//}