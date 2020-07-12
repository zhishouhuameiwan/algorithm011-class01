//组合
#include <iostream>
#include <vector>
using namespace std;

class Solution {
    vector<vector<int>> res;
public:
    vector<vector<int>> combine(int n, int k) {
        vector<int> nums(k, 0);
        helper(nums, n, 1, k, 0);
        return res;
    }

    void helper(vector<int> nums, int n, int i, int k, int j)
    {
        if(j == k)
        {
            res.push_back(nums);
            return ;
        }    
        if(k - j <= n - i) //如果还有可以空的
            helper(nums, n, i + 1, k, j);
        nums[j] = i;
        helper(nums, n, i + 1, k, j + 1);
    }
};
