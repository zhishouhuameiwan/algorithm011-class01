/* 283. 移动零
给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

示例:

输入: [0,1,0,3,12]
输出: [1,3,12,0,0]
说明:

必须在原数组上操作，不能拷贝额外的数组。
尽量减少操作次数。 */


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    //单次遍历
    void moveZeroes_A(vector<int>& nums) {
        int i = 0, j = 0;
        while(i < nums.size())
        {
            if(nums[i++] != 0)
            {
                nums[j++] = nums[i - 1];
                if(i != j)
                    nums[i - 1] = 0;
            }              
        }
    }

    //单次遍历
    void moveZeroes_B(vector<int>& nums) {
        if(nums.size() < 2)
            return;
        for (int i = 0, j = 0; i < nums.size(); i++)
        {
            if(nums[i] != 0)
                swap(nums[i], nums[j++]);
        }
    }

    //单次遍历
    void moveZeroes_C(vector<int>& nums) {
        if(nums.size() < 2)
            return;
        for(int i = 0, j = 0; i < nums.size(); i++)
        {
            if(nums[i] != 0 && j++ != i )
            {
                nums[j - 1] = nums[i];
                nums[i] = 0;                                        
            }
        }
    }

};

int main()
{
    vector<int> nums = {0, 1, 0, 3, 12};
    Solution so;
    //so.moveZeroes_A(nums);
    //so.moveZeroes_B(nums);
    so.moveZeroes_C(nums);

    for(int &num : nums)
        cout << num << " ";
    cout << endl;

    system("pause");
    return 0;
}