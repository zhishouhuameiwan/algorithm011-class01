//全排列II
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
    vector<vector<int>> res;
    vector<int> mNums;
    vector<int> list;
    vector<int> used;
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        mNums = nums;
        used.resize(nums.size(), 0);
        helper();
        return std::move(res);
    }

    void helper()
    {
        if(list.size() == mNums.size())
        {
            res.push_back(list);
            return ;
        }
        for(int i = 0; i < mNums.size(); i++)
        {
            if(used[i] || (i > 0 && (used[i - 1] == 0) && mNums[i] == mNums[i -1]))
                continue;

            used[i] = 1;
            list.push_back(mNums[i]);
            helper();
            list.pop_back();
            used[i] = 0;
        }
    }
};
int main()
{
    vector<int> nums = {1, 2, 1};
    Solution so;
    vector<vector<int>> res = so.permuteUnique(nums);
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