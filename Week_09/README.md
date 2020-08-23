学习笔记
# 高级动态规划
## 算法感触
1. 人肉递归低效，很累。
2. 找到最近最简方法，将其拆解位可重复解决的问题。
3. 数学归纳法思维。
## 动态规划 Dynamic Programming
1. Simplifying a complicated problem by breaking it down into simpler sub-problems
2. Divide & Conquer + Optimal substructure
3. 顺推形式： 动态递推

## 打家劫舍问题
dp[i] 状态定义： max $ of robbing A[0  -> i]
dp[i] = max(dp[i - 2] + nums[i], dp[i - 1])

dp[i][0] 状态定义: max $ of robbing A[0 -> i] 且没偷 nums[i]
dp[i][1] 状态定义: max $ of robbing A[0 -> i] 且偷了 nums[i]
dp[i][0] = max(dp[i - 1][0], dp[i - 1][1])
dp[i][1] = dp[i - 1][0] + nums[i]

## 最小路径和
dp[i][j] 状态定义：minPath(A[1 -> i][1 ->j])
dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + A[i][j]

## 股票买卖
dp[i][k][0 or 1] (0 <= i <= n - 1, 1 <= k <= K)
i 为天数
K 为最多交易次数， k为当前交易次数
[0, 1]为是否持有股票
总状态数：n * K * 2种状态

伪代码如下
```python
for 0 <= i < n:
	for 1 <= k <= K:
		for s in {0, 1}:
			dp[i][k][s] = max(buy, sell, rest)
```
dp[i][k][0] = max(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i])
解释： 今天我没有持有股票，有两种可能
- 我昨天就没有持有股票，然后今天选择rest，所以我今天还是没有持有
- 我昨天持有股票，但是我今天sell了，所以我今天没有持有股票了

dp[i][k][1] = max(dp[i - 1][k][1], dp[i - 1][k][0] - prices[i])
解释：我今天持有股票，有两种可能
- 我昨天就持有股票，然后今天选择rest，所以我今天还持有股票
- 我昨天没有持有，但今天我选择buy，所以今天我就持有股票了

## 高级DP复杂度来源
1. 状态拥有更多的维度，如果当前维度不能解决问题，可以思考增加维度来解决。
2. 状态方程更加复杂。

==编辑距离==

```cpp
/*给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。

你可以对一个单词进行如下三种操作：

插入一个字符
删除一个字符
替换一个字符*/
int minDistance(string word1, string word2) {
    int m = word1.size();
    int n = word2.size();
    if(m * n == 0)
        return m + n;
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for(int i = 0; i <= m; i++)
        dp[i][0] = i;
    for(int j = 0; j <= n; j++)
        dp[0][j] = j;
    for(int i = 1; i <= m; i++)
    {
        for(int j = 1; j <= n; j++)
            dp[i][j] = min(min(dp[i - 1][j] + 1, dp[i][j - 1] + 1), (word1[i - 1] == word2[j - 1] ? 0 : 1 ) + dp[i - 1][j - 1]);
    }
    return dp[m][n];
}
```
==最长有效括号==

```cpp
int longestValidParentheses(string s) {
    if(s.size() < 2)
        return 0;
    int n = s.size();
    vector<int> dp(n, 0);
    int res = 0;
    for(int i = 1; i < n; i++)
    {
        if(s[i] == ')')
        {
            if(s[i - 1] == '(')
                dp[i] = (i > 1 ? dp[i - 2] : 0) + 2;
            else if(i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(')
                dp[i] = dp[i - 1] + (i - dp[i - 1] > 1 ? dp[i - dp[i - 1] - 2] : 0) + 2;
            res = max(res, dp[i]);
        }         
    }
    return res;
}
```
==最长上升子序列==

```cpp
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
```
==通配符匹配==

```cpp
/*给定一个字符串 (s) 和一个字符模式 (p) ，实现一个支持 '?' 和 '*' 的通配符匹配。*/
bool isMatch(string s, string p) {
    int m = s.size();
    int n = p.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    dp[0][0] = 1;
    for(int i = 1; i <= n; ++i)
    {
        if(p[i - 1] == '*')
            dp[0][i] = 1;
        else
            break;
    }

    for(int i = 1; i <= m; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            if(p[j - 1] == '*')
                dp[i][j] = dp[i][j - 1] | dp[i - 1][j];                     
            else if(s[i - 1] == p[j - 1] || p[j - 1] == '?')
                dp[i][j] = dp[i - 1][j - 1];
        }
    }
    return dp[m][n];
}
```

# 字符串算法
字符串操作很常见，在C/C++中string为可变字符串，变化string内字符时候，string变量是不变的，但是Java和Python内字符串是不可变的，如果改变字符串内字符，则生成一个新的字符串变量。

== 最长公共子序列==

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
==最长回文子串==

```cpp
pair<int, int> expandAroundCenter(const string& s, int left, int right) {
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        --left;
        ++right;
    }
    return {left + 1, right - 1};
}

string longestPalindrome(string s) {
    int start = 0, end = 0;
    for (int i = 0; i < s.size(); ++i) {
        auto [left1, right1] = expandAroundCenter(s, i, i);
        auto [left2, right2] = expandAroundCenter(s, i, i + 1);
        if (right1 - left1 > end - start) {
            start = left1;
            end = right1;
        }
        if (right2 - left2 > end - start) {
            start = left2;
            end = right2;
        }
    }
    return s.substr(start, end - start + 1);
}
```
##  字符串匹配算法
1. 暴力法
2.  Rabin-Karp 算法
3. KMP 算法

== 暴力算法==

```cpp
int forceSearch(string text, string pattern) {
    int len_txt = text.length();
    int len_pat = pattern.length();

    for (int i = 0; i <= len_txt - len_pat; i++) {
        int j = 0;
        for (j = 0; j < len_pat; j++) {
            if (text[i + j] != pattern[j]) break;
        }
        if (j == len_pat) {
            return i;
        }
    }
    return -1;
}
```
## Rabin-Karp 算法
算法思想：
1. 假设字串的长度为M(pat)，目标字符串的长度为N(txt)
2. 计算字串的hash值 hash_pat
3. 计算目标字符串txt中每个长度为M的字串的hash值（共需要计算N-M+ 1次）
4. 比较hash值：如果hash值不同，字符串必然不匹配，如果hash值相同，还需要使用朴素算法再次进行判断。

```cpp
const int D = 256;
const int Q = 9997;

int RabinKarpSerach(string txt, string pat) {
    int M = pat.length();
    int N = txt.length();
    int i, j;
    int patHash = 0, txtHash = 0;

    for (i = 0; i < M; i++) {
        patHash = (D * patHash + pat[i]) % Q;
        txtHash = (D * txtHash + txt[i]) % Q;
    }
    int highestPow = 1;  // pow(256, M-1)
    for (i = 0; i < M - 1; i++) 
        highestPow = (highestPow * D) % Q;

    for (i = 0; i <= N - M; i++) { // 枚举起点
        if (patHash == txtHash) {
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j])
                    break;
            }
            if (j == M)
                return i;
        }
        if (i < N - M) {
            txtHash = (D * (txtHash - txt[i] * highestPow) + txt[i + M]) % Q;
            if (txtHash < 0)
                txtHash += Q;
        }
    }

    return -1;
}
```


## KMP
KMP算法（Knuth-Morris-Pratt）的思想就是，当字串与目标字符串不匹配时，其实你已经知道了前面已经匹配成功的那一部分的字符（包括字串与目标字符串）。以大佬的博客内容 [字符串匹配的KMP算法](http://www.ruanyifeng.com/blog/2013/05/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm.html)为例， 当空格与D不匹配时，你其实知道前面六个字符是"ABCDAB"。KMP算法的思想是，设法利用这个已知信息，不要把“搜索位置”移回到已经比较过的位置，继续把它向后移，这样就提高了效率。
[KMP字符串匹配算法视频](https://www.bilibili.com/video/av11866460?from=search&seid=17425875345653862171)