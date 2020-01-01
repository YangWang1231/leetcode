#include<vector>
#include<iostream>
#include<algorithm>
using std::cout;
using std::vector;





vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
	/*std::sort(std::begin(points), std::end(points),
		[](auto point1, auto point2) { return (point1[1] * point1[1] + point1[0] * point1[0]) < (point2[0] * point2[0] + point2[1] * point2[1]); });
		*/

	std::nth_element(std::begin(points), std::begin(points) + K, std::end(points),
		[](auto point1, auto point2) { return (point1[1] * point1[1] + point1[0] * point1[0]) < (point2[0] * point2[0] + point2[1] * point2[1]); });
	return vector(std::begin(points), std::begin(points) + K);


}

//void main()
//{
//	int k = 2;
//	vector<vector<int>> input{ {3,3}, {5, -1},{-2, 4} };
//	vector < vector<int>> output = kClosest(input,k);
//	for (auto point : output) {
//		cout << "{" << point[0] << "," << point[1] << "}" << std::endl;
//	}
//}