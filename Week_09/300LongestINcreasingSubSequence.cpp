//300 最长上升子序列
#include <iostream>
#include <vector>

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if(nums.size() < 1)
            return 0;
        int n = nums.size();
        vector<int> dp(n + 1, 0);
        int len = 1;
        dp[len] = nums[0];
        for(int i = 1; i < n; i++)
        {
            if(dp[len] < nums[i])
                dp[++len] = nums[i];
            else
            {
                int left = 1, right = len;
                while(left <= right)
                {
                    int mid = (left + right) >> 1;
                    if(dp[mid] < nums[i])
                        left = mid + 1;
                    else
                        right = mid - 1;                  
                }
                dp[left] = nums[i];
            }
        }
        return len;
    }
};