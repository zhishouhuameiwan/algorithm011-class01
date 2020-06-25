/* 1. 两数之和
给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。

 

示例:

给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1] */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    //两遍hash
    vector<int> twoSum_A(vector<int>& nums, int target) {
        unordered_map<int, int> hashmap;
        for (int i = 0; i < nums.size(); i++)
        {
            hashmap.insert(make_pair(nums[i], i));
        }

        for (int i = 0; i < nums.size(); i++)
        {
            int temp = target - nums[i];
            if(hashmap.find(temp) != hashmap.end() && hashmap[temp] != i)
            {
                return {i, hashmap[temp]};
            }
        }
    }

    //单遍hash
    vector<int> twoSum_B(vector<int>& nums, int target) {
        unordered_map<int, int> hashmap;
        for (int i = 0; i < nums.size(); i++)
        {
            if(hashmap.count(target - nums[i]) > 0)
            {
                return {hashmap[target - nums[i]], i};
            }
            hashmap[nums[i]] = i;
        }
        return {};
    }
};


int main()
{
    vector<int> nums = {2, 7, 11, 15};
    Solution so;
    //vector<int> res = so.twoSum_A(nums, 9);
    vector<int> res = so.twoSum_B(nums, 9);

    for(int &num : res)
        cout << num << " ";
    cout << endl;

    system("pause");
    return 0;
}