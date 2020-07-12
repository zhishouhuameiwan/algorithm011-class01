//全排列
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;


//Definition for a binary tree node.
class Solution {
    vector<vector<int>> res;
    vector<int> mNums;
    vector<int> list;
    vector<int> used;
public:
    vector<vector<int>> permute(vector<int>& nums) {
        mNums = nums;
        list.resize(nums.size());
        used.resize(nums.size(), 0);
        helper(0);
        return std::move(res);
    }

    void helper(int j)
    {
        if(j == mNums.size())
        {
            res.push_back(list);
            return ;
        }
        for(int i = 0; i < mNums.size(); i++)
        {
            if(used[i] == 0)
            {
                used[i] = 1;
                list[j] = mNums[i];
                helper(j + 1);
                used[i] = 0;
            }
        }
    }
};

int main()
{
    vector<int> nums = {1, 2, 3};
    Solution so;
    vector<vector<int>> res = so.permute(nums);
    for(auto &list : res)
    {
        for(auto &num : list)
        {
            cout << num << " ";
        }
        cout << endl;
    }
    system("pause");
    return 0;
}