//solution of house robber II

#include<vector>	
#include<algorithm>
using namespace std;

namespace HOUSE_ROBBER_II {
	vector<int> money_v1;
	vector<int> money_v2;
	vector<int> copy_val;
	//vector<int> val{ 1,2,3,1 };
	vector<int> val{ 114,117,207,117,235,82,90,67,143,146,53,108,200,91,80,223,58,170,110,236,81,90,222,160,165,195,187,199,114,235,197,187,69,129,64,214,228,78,188,67,205,94,205,169,241,202,144,240};

	

	int cal_rob2(vector<int>& nums, vector<int>& money_v)
	{
		if (nums.size() == 0)
			return 0;
		else if (nums.size() == 1)
		{
			return nums[0];
		}
		else if (nums.size() == 2)
		{
			return max(nums[0], nums[1]);
		}
		else {
			money_v[0] = nums[0];
			money_v[1] = max(nums[1], nums[0]);
			for (int i = 2; i < nums.size(); i++)
			{
				money_v[i] = max(nums[i] + money_v[i - 2], money_v[i - 1]);
			}
		}

		return money_v.back();
	}

	int rob(vector<int>& nums)
	{
		if (nums.size() == 0)
			return 0;
		else if (nums.size() == 1) {
			return nums.front();
		}
		else if (nums.size() == 2) {
			return max(nums.front(), nums.back());
		}

		copy_val.resize(nums.size());
		money_v1.resize(nums.size());
		money_v2.resize(nums.size());
		copy(nums.begin(), nums.end(), copy_val.begin());

		nums.front() = 0;
		copy_val.back() = 0;

		int result1 = cal_rob2(nums,money_v1);
		int result2 = cal_rob2(copy_val, money_v2);
		int result = max(result1, result2);
		printf("max rob value is %d\n", result);
		return result;

	}
	////////////////////////////////
	//not right answer
	class rob_result
	{
	public:
		rob_result() :result(0), from_first(false) {}
		~rob_result() {}
		rob_result& operator = (int val) {
			result = val;
			return *this;
		}

		rob_result& operator + (int val) {
			result += val;
			return *this;
		}

	public:
		int result;
		bool from_first;
	};

	vector<rob_result> money;

	int rob_smaller(vector<int>& nums)
	{
		if (nums.size() == 0)
			return 0;
		else if (nums.size() == 1) {
			return nums.front();
		}
		else if (nums.size() == 2) {
			return max(nums.front(), nums.back());
		}

		money.resize(nums.size());
		money[0] = nums[0];
		money[0].from_first = true;
		money[1] = nums[1];
		auto length = nums.size();
		auto com = [](const rob_result& l, const rob_result& r) { return l.result < r.result;  };
		money[1] = max(money[0], money[1], com);

		for (int i = 2; i < length -1; i++)
		{
			money[i] = max(money[i - 2] + nums[i], money[i - 1], com);
		}
		
		if (money[length - 3].from_first) {
			money.back() = max(money[length - 3], money[length - 2], com);
		}
		else
		{
			money.back() = max(money[length - 3] + nums.back(), money[length - 2], com);
		}

		printf("max rob value is %d\n", money.back().result);
		return money.back().result;

	}
	////////////////////////////////

}



//void main()
//{
//	HOUSE_ROBBER_II::rob(HOUSE_ROBBER_II::val); //right
//	//HOUSE_ROBBER_II::rob_smaller(HOUSE_ROBBER_II::val); //wrong
//}