学习笔记

# 动态规划
从分治，回溯，递归一直到动态规划，本质上算法思维没有大的区别，都是把复杂问题分解为它的子问题，同时寻找它的重复性。

## 感触
1. 人肉递归低效，而且很累
2. 找到最近最简方法，将其拆分为可重复解决的问题。
3. 数学归纳思维。（先将基本条件想清楚，比如n = 1，n = 2时候是什么样，n怎么推导n + 1）。

## 动态规划的定义
Simplifying a complicated problem by breaking it down into simpler sub-problems.(in  a recursive manner)
动态规划一般用来解决最优解，最大值或者求一个最少的方式。因为动态规划是最优子结构来组成的，所以不需要存储所有的值，只需要能够证明从最优子结构能够推导出全局最优解就OK了。

## 动态规划与递归分治
**本质上没有区别
共性： 找到重复子问题
差异性：最有子结构、中途可以淘汰次优解**

### 动态规划的关键点：
1. 最优子结构 dp[n] = best_of(dp[n - 1], dp[n - 2],...)
2. 储存中间状态 dp[i]
3. 递推公式（状态转移方程或者dp方程）
	Fib：dp[i] = dp[i - 1] + dp[i - 2]
	二维路径：dp[i][j] = dp[i + 1][j] + dp[i][j + 1] (且判定a[i][j]是否为空地)



			不同路径一个机器人位于一个 m x n 网格的左上角，需要走到右下角，网格中的障碍物和空位置分别用 1 和 0 来表示。一共有多少种走法
			

```cpp
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = (obstacleGrid[0][0] == 0);
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(obstacleGrid[i][j] == 1)
            {
                dp[i][j] = 0;
                continue;
            }
            if(i > 0)
                dp[i][j] += dp[i - 1][j];
            if(j > 0)
                dp[i][j] += dp[i][j - 1];
        }
    }
    return dp[m - 1][n - 1];
}
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    vector<int> dp(n, 0);
    dp[0] = 1;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(obstacleGrid[i][j] == 1)
            {
                dp[j] = 0;
                continue;
            }
            if(j > 0)
                dp[j] += dp[j - 1];
        }
    }
    return dp.back();
}
```
			给定两个字符串，返回两个字符串的最长公共子序列
	

```cpp
int longestCommonSubsequence(string text1, string text2) {
    int m = text1.size(), n = text2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1 ,0));
    for(int i = 1; i <= m; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(text1[i - 1] == text2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j -1]);
        }
    }
    return dp[m][n];
}
```

			给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。
		

```cpp
int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    dp[0][0] = triangle[0][0];
    for(int i = 1; i < n; i++)
    {
        dp[i][0] = triangle[i][0] + dp[i - 1][0];  //第一列
        for(int j = 1; j < i; j++)
            dp[i][j] = triangle[i][j] +  min(dp[i - 1][j], dp[i - 1][j - 1]);
        dp[i][i] = triangle[i][i] + dp[i - 1][i - 1]; //最后一列
    }
    return *min_element(dp[n - 1].begin(), dp[n - 1].end());
}

int minimumTotal(vector<vector<int>>& triangle) {
    vector<int> dp(triangle.back());
    for(int i = triangle.size() - 2; i >= 0; i --)
        for(int j = 0; j <= i; j ++)
            dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
    return dp[0];
}
```
			最长有效括号
			
```cpp
int longestValidParentheses(string s) {
    if(s.size() < 2)
        return 0;
    int n = s.size();
    vector<int> dp(n, 0);
    int res = 0;
    for (int i = 1; i < n; i++)
    {
        if(s[i] == ')')
        {
            if(s[i - 1] == '(')
                dp[i] = (i > 1 ? dp[i - 2] : 0) + 2;
            else if(i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(')
                dp[i] = dp[i - 1] + 2 + (i - dp[i - 1] > 1 ? dp[i - dp[i - 1] - 2] : 0);
            res = max(res, dp[i]);
        }
    }
    return res;
}
```
			最大子序列和
			

```cpp
int maxSubArray(vector<int>& nums) {
    if(nums.size() < 1)
        return 0;
    int res = nums[0];
    for(int i = 1; i < nums.size(); i++)
    {
        nums[i] += max(nums[i - 1], 0);
        res = max(res, nums[i]);
    }          
    return res;
}
```
			零钱兑换，给定不同面额的硬币 coins 和一个总金额 amount，计算可以凑成总金额所需的最少的硬币个数。
			
```cpp
int coinChange(vector<int>& coins, int amount) {
    if(coins.size() < 1)
        return -1;
    if(amount < 1)
        return 0;
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    for(int i = 1; i <= amount; i++)
    {
        for(int &c : coins)
            if(c <= i)
                dp[i] = min(dp[i], dp[i - c] + 1);
    }
    return dp[amount] > amount ? -1 : dp[amount];
}
```
			打家劫舍， 不能连续偷两家相邻的房子
	
```cpp
int rob(vector<int>& nums) {
    int prev = 0, cur = 0, tm = 0;
    for(int i = 0; i < nums.size(); i++)
    {
        tm = cur;
        cur = max(prev + nums[i], cur);
        prev = tm;
    }
    return cur;
}
```
			打家劫舍2，环形房子，首尾相连
			

```cpp
//解题思路，不偷首家与不偷尾家各计算一次，找到最大值
int rob(vector<int>& nums) {
    if(nums.size() < 1)
        return 0;
    
    if(nums.size() < 2)
        return nums[0];
    
    int n = nums.size();
    return max(helper(nums, 0, n - 2), helper(nums, 1, n -1));
}

int helper(vector<int>& nums, int start, int end)
{
    int prev = 0, cur = 0, tm = 0;
    for(int i = start; i <= end; i++)
    {
        tm = cur;
        cur = max(nums[i] + prev, cur);
        prev = tm;
    }
    return cur;
}
```
			买卖股票的最佳时机 II
			
```cpp
int maxProfit(vector<int>& prices) {
    if(prices.size() < 1)
        return 0;
    int f0 = -prices[0], f1 = 0;
    //f0 代表手里有一只股票， f1 代表手里没有股票，通过循环递推
    for(int i = 1; i < prices.size(); i++)
    {
        int t = f0;
        f0 = max(f0, f1 - prices[i]);
        f1 = max(t + prices[i], f1);
    }
    return f1;
}
```
			买卖股票的最佳时机，含冷冻期
			
```cpp
int maxProfit(vector<int>& prices) {
    if(prices.size() < 1)
        return 0;
    int n = prices.size();
    int f0 = -prices[0], f1 = 0, f2 = 0;
    //f0 代表手里有一只股票， f1 代表手里没有股票，且在冷却   f2代表没有股票，且不在冷却 通过循环递推
    for(int i = 1; i < n; i++)
    {
        int t0 = f0, t1 = f1;
        f0 = max(f0, f2 - prices[i]);
        f1 = t0 + prices[i];
        f2 = max(t1, f2);
    }
    return max(f1, f2);
}
```
解决所有股票问题的思路，参考 [一个方法团灭 6 道股票问题](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/solution/yi-ge-fang-fa-tuan-mie-6-dao-gu-piao-wen-ti-by-l-3/) 中大佬的文章。