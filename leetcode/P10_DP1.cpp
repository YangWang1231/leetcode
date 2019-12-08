/*
recrusive solution for regression string matching.
top down method.
*/

#include<vector>
#include<string>
using namespace std;

namespace P10_DP1{
class record
{
public:
	record():result{false}, count{-1}{}

	bool result;
	int  count;
};

typedef vector<vector<record>> metrix;

metrix g_memo;

void init_metrix(int row, int col)
{
	g_memo.resize(row + 1);
	for (auto& row_vec : g_memo) {
		row_vec.resize(col + 1);
	}
}

bool match_str(int i, int j, const string& s, const string& p)
{
	if (g_memo[i][j].count != -1) {
		g_memo[i][j].count++;
		return g_memo[i][j].result;
	}

	bool result = false;

	if (j >= p.length()) {
		result = i >= s.length();
		g_memo[i][j].result = result;
		g_memo[i][j].count = 1;
		return result;
	}

	bool firstmatch = (i < s.length()) && ((s[i] == p[j]) || (p[j] == '.'));
	if (j + 1 < p.length() && p[j + 1] == '*') {
		result = match_str(i, j + 2, s, p) || (firstmatch && match_str(i + 1, j, s, p));
	}
	else {
		result = firstmatch && match_str(i + 1, j + 1, s, p);
	}

	g_memo[i][j].result = result;
	g_memo[i][j].count = 1;

	return result;
}

bool isMatch(string s, string p)
{
	init_metrix(s.length(), p.length());
	return match_str(0, 0, s, p);
}
}
static string s = "abaaaaaabcbbbccabab";
static string p = ".*ba*a*aba*cb*bc*abab";
#include<algorithm>
//void main()
//{
//	bool result = P10_DP1::isMatch(s, p);
//	int maxcount = 0;
//	for (auto row : P10_DP1::g_memo) {
//		for (auto elem : row) {
//			maxcount = max(maxcount, elem.count);
//			printf("{match result : %s, access count: %d}\t", elem.result?"true":"false", elem.count);
//		}
//
//		printf("\n");
//	}
//	printf("max count : %d", maxcount);
//}