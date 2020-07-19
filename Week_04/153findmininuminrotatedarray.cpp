//153. 寻找旋转排序数组中的最小值

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
     int findMin(vector<int>& nums) {
        if(nums.size() < 1)
            return -1;
        if (nums.size() == 1) {
            return nums[0];
        }
        int left = 0, right = nums.size() - 1;
        if (nums[right] > nums[0]) {
            return nums[0];
        }
        
        while (right >= left) 
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[mid + 1]) {
                return nums[mid + 1];
            }
            if (nums[mid - 1] > nums[mid]) {
                return nums[mid];
            }

            if (nums[mid] > nums[0]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }
};

int main()
{
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    Solution so;
    cout << so.findMin(nums) << endl;
    system("pause");
    return 0;
}