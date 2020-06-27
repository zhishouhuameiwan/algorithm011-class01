/* 66. 加一
给定一个由整数组成的非空数组所表示的非负整数，在该数的基础上加一。

最高位数字存放在数组的首位， 数组中每个元素只存储单个数字。

你可以假设除了整数 0 之外，这个整数不会以零开头。

示例 1:

输入: [1,2,3]
输出: [1,2,4]
解释: 输入数组表示数字 123。
示例 2:

输入: [4,3,2,1]
输出: [4,3,2,2]
解释: 输入数组表示数字 4321。 */

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> plusOne_A(vector<int>& digits) {
        vector<int> res(digits.size());
        int tm = 1;
        for(int i = digits.size() - 1; i >= 0; i--)
        {
            res[i] = (digits[i] + tm) % 10;
            tm = (digits[i] + tm) / 10;
        }
        if(tm > 0)
        {
            res.insert(res.begin(), tm);
        }
        return res;
    }

    vector<int> plusOne_B(vector<int>& digits) {
        for(int i = digits.size() - 1; i >= 0; i--)
        {                    
            if(digits[i] == 9)
                digits[i] = 0;
            else
            {
                digits[i] += 1; 
                break;
            }                          
        }
        if(digits[0] == 0)
        {
            digits[0] = 1;
            digits.push_back(0);
        }
        return digits;
    }

    vector<int> plusOne_C(vector<int>& digits) {
        for(int i = digits.size() - 1; i >= 0; i--)
        {
            digits[i]++;
            if(digits[i] != 10)
                return digits;
            else
                digits[i] = 0;                                          
        }
        if(digits[0] == 0)
        {
            digits[0] = 1;
            digits.push_back(0);
        }
        return digits;
    }
};



int main()
{
    vector<int> nums1 = {1, 2, 3};

    Solution so;
    //so.plusOne_A(nums1, 3, nums2, 3);
    //so.plusOne_B(nums1, 1, nums2, 1);
    so.plusOne_C(nums1);

    for(int &num : nums1)
        cout << num << " ";
    cout << endl;

    system("pause");
    return 0;
}