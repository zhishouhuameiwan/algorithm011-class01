// 32. 最长有效括号
// 给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
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
};

int main()
{
    string s = "(()))";
    Solution so;
    cout << so.longestValidParentheses(s) << endl;

    system("pause");
    return 0;
}