/* 189. 旋转数组
给定一个数组，将数组中的元素向右移动 k 个位置，其中 k 是非负数。

示例 1:

输入: [1,2,3,4,5,6,7] 和 k = 3
输出: [5,6,7,1,2,3,4]
解释:
向右旋转 1 步: [7,1,2,3,4,5,6]
向右旋转 2 步: [6,7,1,2,3,4,5]
向右旋转 3 步: [5,6,7,1,2,3,4]
示例 2:

输入: [-1,-100,3,99] 和 k = 2
输出: [3,99,-1,-100]
解释: 
向右旋转 1 步: [99,-1,-100,3]
向右旋转 2 步: [3,99,-1,-100]
说明:

尽可能想出更多的解决方案，至少有三种不同的方法可以解决这个问题。
要求使用空间复杂度为 O(1) 的 原地 算法。 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    //使用队列，空间复杂度为O(n)，不符合要求
    void rotate_A(vector<int>& nums, int k) {
        k = k % nums.size();
        if(k == 0)
            return;
        queue<int> qu;
        for (int i = nums.size() - 1; i >= 0; i--)
            qu.push(nums[i]);

        for (int i = 0; i < k; i++)
        {
            qu.push(qu.front());
            qu.pop();
        }

        for (int i = nums.size() - 1; i >= 0; i--)
        {
            nums[i] = qu.front();
            qu.pop();
        }
    }

    //暴力循环
    void rotate_B(vector<int>& nums, int k) {
        k = k % nums.size();
        if(k == 0)
            return;
        for (int step = 0; step < k; step++)
        {
            int cache = nums[nums.size() - 1];
            for (int i = 0; i < nums.size(); i++)
            {
                int temp = nums[i];
                nums[i] = cache;
                cache = temp;
            }
        }
    }

    //使用直接设置值的方法，时间O(n) 空间O(1)
    void rotate_C(vector<int>& nums, int k) {
        k = k % nums.size();
        if(k == 0)
            return;
        int count = 0;
        for (int start = 0; count < nums.size(); start++)
        {
            int cache = nums[start];
            int i = start;
            do
            {
                i = (i + k) % nums.size();
                swap(nums[i], cache);
                count++;
            } while (i != start);
        }       
    }

    //使用反转方法
    void rotate_D(vector<int>& nums, int k) {
        k = k % nums.size();
        if(k == 0)
            return;
        reverseMy(nums, 0, nums.size() - 1);
        reverseMy(nums, 0, k - 1);
        reverseMy(nums, k, nums.size() - 1);
    }

    void reverseMy(vector<int> &nums, int left, int right)
    {
        while(left < right)
        {
            swap(nums[left++], nums[right--]);
        }
    }

    //使用stl库 rotate
    void rotate_E(vector<int>& nums, int k) {
        std::rotate(nums.begin(), nums.begin() + k % nums.size(), nums.end());
    }

    //stl库
    void rotate_F(vector<int>& nums, int k) {
        std::reverse(nums.begin(), nums.end() - k % nums.size());
        std::reverse(nums.end() - k % nums.size(), nums.end());
        std::reverse(nums.begin(), nums.end());
    }

};

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
    Solution so;
    //so.rotate_A(nums, 3);
    //so.rotate_B(nums, 3);
    //so.rotate_C(nums, 3);
    //so.rotate_D(nums, 3);
    //so.rotate_E(nums, 3);
    so.rotate_F(nums, 3);

    for (int i = 0; i < nums.size(); i++)
        cout << nums[i] << " ";
    cout << endl;

    system("pause");
    return 1;
}
