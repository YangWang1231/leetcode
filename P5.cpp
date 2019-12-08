//solution for Longest Palindromic Substring
#include<string>
#include<vector>
#include<algorithm>
using namespace std;


namespace P5 {

	typedef vector<vector<bool>> metrix;

	metrix g_memo;

	void init_metrix(int row, int col)
	{
		g_memo.resize(row);
		for (auto& row_vec : g_memo) {
			row_vec.resize(col);
			for (int i = 0; i < row_vec.size(); ++i) {
				row_vec[i] = false;
			}
		}
	}

	//bool 

	string longestPalindrome(string s) {
		pair<int, int> max_pair{ 0,0 };

		for (int i = 0; i < s.length(); ++i) {
			for (int j = i; j < s.length(); ++j) {
				if (s[i] == s[j]) {
					g_memo[i][j] = true;
				}
			}
		}

		for (auto row : g_memo) {
			for (auto elem : row) {
				printf("%s\t", elem == true ? "true" : "false");
			}
			puts("\n");
		}
		
		for (int i = 0; i < s.length(); ++i) {
			int j; int k;
			for (j = s.length(), k = i; j >= i && g_memo[k][j]; --j)
				;
			max_pair = max(max_pair, make_pair(i, j), 
				[] (const pair<int, int>& pair1, const pair<int, int>& pair2) {return (pair1.second - pair1.first) < (pair2.second - pair2.first) ;  });
		}



		return "hello";
	}

}//end of namespace P5

string input_s = "acdbbd"; //"babab";

//void main()
//{
//	P5::init_metrix(input_s.length(), input_s.length());
//	string result = P5::longestPalindrome(input_s);
//}