//solution of house robber 

#include<vector>	
#include<algorithm>
using namespace std;

vector<int> money_v;

int cal_rob(int index)
{
	int lenght = money_v.size();
	if (lenght == index + 2)
	{
		return max(money_v[index], money_v[index + 1]);
	}
	else if (lenght == index + 1)
	{
		return money_v[index];
	}
	else {
		return max(money_v[index] + cal_rob(index + 2), cal_rob(index + 1));
	}
}

int cal_rob2(vector<int>& nums)
{
	if (nums.size() == 0)
		return 0;
	else if(nums.size() == 1)
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
	money_v.resize(nums.size());
	int result = cal_rob2(nums);
	printf("max rob value is %d\n", result);
	return result;

	//money_v.resize(nums.size());
	//copy(nums.begin(), nums.end(), money_v.begin());
	//int result = cal_rob(0);
	//printf("max rob value is %d\n", result);
	//return result;
}

//vector<int> val{ 114,117,207,117,235,82,90,67,143,146,53,108,200,91,80,223,58,170,110,236,81,90,222,160,165,195,187,199,114,235,197,187,69,129,64,214,228,78,188,67,205,94,205,169,241,202,144,240};

vector<int> val{ 2, 1, 1, 2 };

//void main()
//{
//	rob(val);
//}
