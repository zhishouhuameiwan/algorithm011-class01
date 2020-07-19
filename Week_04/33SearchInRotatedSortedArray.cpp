//33 搜索旋转排序数组

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(nums.size() < 1)
            return -1;
        int left = 0, right = nums.size() - 1;
        while(left <= right)
        {
            int mid = ((right + left + 1) >> 1);
            if(nums[mid] == target)
                return mid;
            if(nums[mid] > nums[left])
            {
                if(nums[mid] < target || nums[left] > target)
                    left = mid + 1;
                else
                    right = mid - 1;
            }
            else
            {
                if(nums[mid] > target || nums[right] < target)
                    right = mid - 1;
                else
                    left = mid + 1;
            }
        }
        return -1;
    }
};

int main()
{
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    Solution so;
    cout << so.search(nums, 0) << endl;
    system("pause");
    return 0;
}