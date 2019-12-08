/*
recrusive solution for regression string matching.
down-top method
*/

#include<vector>
#include<string>
using namespace std;

namespace P10_DP2 {
	class record
	{
	public:
		record() :result{ false }, count{ -1 }{}

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
		//very important. the init state.
		
		g_memo[row][col].result = true;
	}

	bool match_str(const string& s, const string& p)
	{
		for (int i = s.length() ; i >= 0; --i) {
			for (int j = p.length() - 1; j >= 0; --j) {
				bool first_match = (i < s.length()) && (s[i] == p[j] || p[j] == '.');
				if (j + 1< p.length() && p[j + 1] == '*') {
					g_memo[i][j].result = g_memo[i][j + 2].result || (first_match && g_memo[i + 1][j].result);
				}
				else
					g_memo[i][j].result = first_match && g_memo[i + 1][j + 1].result;
			}
		}

		
		return g_memo[0][0].result;
	}

	bool isMatch(string s, string p)
	{
		init_metrix(s.length(), p.length());
		return match_str(s, p);
	}
}
//static string s = "abaaaaaabcbbbccabab";
//static string p = ".*ba*a*aba*cb*bc*abab";
static string s = "aa";
static string p = "a*";

#include<algorithm>
//void main()
//{
//	bool result = P10_DP2::isMatch(s, p);
//	int maxcount = 0;
//	for (auto row : P10_DP2::g_memo) {
//		for (auto elem : row) {
//			maxcount = max(maxcount, elem.count);
//			printf("{match result : %s, access count: %d}\t", elem.result ? "true" : "false", elem.count);
//		}
//
//		printf("\n");
//	}
//	//printf("max count : %d", maxcount);
//}