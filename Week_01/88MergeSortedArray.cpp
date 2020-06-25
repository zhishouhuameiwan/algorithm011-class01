/* 88. 合并两个有序数组
给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。

 

说明:

初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。
你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
 

示例:

输入:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

输出: [1,2,2,3,5,6] */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    //sort
    void merge_A(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for (int i = m; i < m + n; i++)
        {
            nums1[i] = nums2[i - m];
        }
        sort(nums1.begin(), nums1.end());
    }

    //新开数组
    void merge_B(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if(n < 1)
            return;
        vector<int> nums3(m);
        std::copy(nums1.begin(), nums1.begin() + m, nums3.begin());

        int i = 0, j = 0, k = 0;
        while(i < m && j < n)
        {
            nums1[k++] = nums2[j] > nums3[i] ? nums3[i++] : nums2[j++];
        }
        if(i < m)
            std::copy(nums3.begin() + i, nums3.end(), nums1.begin() + k);
        if(j < n)
            std::copy(nums2.begin() + j, nums2.end(), nums1.begin() + k);
    }

    //双指针
    void merge_C(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if(n < 1)
            return;

        int i = m - 1;
        int j = n - 1;
        int k = m + n - 1;
        while(i >= 0 && j >= 0)
        {
            nums1[k--] = nums1[i] > nums2[j] ? nums1[i--] : nums2[j--];
        }
        if(j >= 0)
            std::copy(nums2.begin(), nums2.begin() + j + 1, nums1.begin());
    }
};


int main()
{
    vector<int> nums1 = {2, 0};
    vector<int> nums2 = {1};

    Solution so;
    //so.merge_A(nums1, 3, nums2, 3);
    //so.merge_B(nums1, 1, nums2, 1);
    so.merge_C(nums1, 1, nums2, 1);

    for(int &num : nums1)
        cout << num << " ";
    cout << endl;

    system("pause");
    return 0;
}