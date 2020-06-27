/* 42. 接雨水
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。



上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 感谢 Marcos 贡献此图。

示例:

输入: [0,1,0,2,1,0,1,3,2,1,2,1]
输出: 6 */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    //暴力法，将每个格能接的雨水依次相加
    int trap_A(vector<int>& height) {
        if(height.size() < 3)
            return 0;
        int res = 0;
        for (int i = 1; i < height.size() - 1; i++)
        {
            int maxLeft = height[i], maxRight = height[i];
            for (int j = i - 1; j >= 0; j--)
                maxLeft = max(maxLeft, height[j]);
            for (int k = i + 1; k < height.size(); k++)
                maxRight = max(maxRight, height[k]);
            res += min(maxLeft, maxRight) - height[i];
        }
        return res;
    }

    //动态编程
    int trap_B(vector<int>& height) {
        if(height.size() < 3)
            return 0;
        int res = 0;
        int size = height.size();
        vector<int> maxLeft(size), maxRight(size);
        maxLeft[0] = height[0];
        for (int i = 1; i < size; i++)
            maxLeft[i] = max(maxLeft[i - 1], height[i]);
        maxRight[size - 1] = height[size - 1];
        for (int j = size - 2; j >= 0; j--)
            maxRight[j] = max(maxRight[j + 1], height[j]);
        for (int k = 1; k < size - 1; k++)
            res += min(maxLeft[k], maxRight[k]) - height[k];
        return res;
    }

    //栈
    int trap_C(vector<int>& height){
        if(height.size() < 3)
            return 0;
        int res = 0, i = 0;
        stack<int> st;
        while(i < height.size())
        {
            while(!st.empty() && height[st.top()] < height[i])
            {
                int top = st.top();
                st.pop();
                if(st.empty())
                    break;
                int dis = i - st.top() - 1;
                int boundHeight = min(height[i], height[st.top()]) - height[top];
                res += dis * boundHeight;
            }
            st.push(i++);
        }
        return res;
    }

    //双指针
    int trap_D(vector<int>& height){
        if(height.size() < 3)
            return 0;
        int res = 0, left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        while(left < right)
        {
            if(height[left] < height[right])
            {
                height[left] >= leftMax ? leftMax = height[left] : res += leftMax - height[left];
                left++;
            }
            else
            {
                height[right] >= rightMax ? rightMax = height[right] : res += rightMax - height[right];
                right--;
            }
        }
        return res;
    }
};

int main()
{
    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

    Solution so;

    //int trap = so.trap_A(height);
    //int trap = so.trap_B(height);
    //int trap = so.trap_C(height);
    int trap = so.trap_D(height);

    cout << "trap:" << trap << endl;

    system("pause");

    return 0;
}