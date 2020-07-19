学习笔记
## 贪心算法

贪心算法是一种在每一步选择中都采取在当前状态下最好或最优的选择，从而希望导致结果是全局最好的或最优的算法。
贪心算法与动态规划的不同在于它对于每个子问题的解决方案都做出选择，不能回退。动态规划则会保存以前的运算结果，并根据以前的结果对当前进行选择，有回退功能。
贪心法可以解决一些最优化问题，如：求图中的最小生成树，求哈夫曼编码等。然而对于工程和生活中的问题，贪心法一般不能得到我们所要求的答案。
一旦一个问题可以通过贪心法来解决，那么贪心法一般是解决这个问题的最好办法。由于贪心法的高效性以及其所求的答案比较接近最优结果，贪心法也可以用作辅助算法或者直接解决一些要求结果不特别精确的问题。

### 适用贪心算法的场景
简单的说，问题能够分解成子问题来解决，子问题的最优解能递推到最终问题的最优解，这种子问题的最优解称为最优子结构。

		买卖股票的最佳时机 II
		
```cpp
int maxProfit(vector<int>& prices) 
{
     if(prices.size() < 1)
         return 0;
     int f0 = -prices[0], f1 = 0;
     //f0 代表手中有一只股票，该天可以卖出 
     //f1 代表手中没有股票的情况，该天可以买进
     for(int i = 1; i < prices.size(); i++)
     {
         int t = f0;
         f0 = max(f0, f1 - prices[i]);
         f1 = max(t + prices[i], f1);
     }
     return f1;
}
```
			跳跃游戏给定一个非负整数数组，你最初位于数组的第一个位置。
			数组中的每个元素代表你在该位置可以跳跃的最大长度。
			判断你是否能够到达最后一个位置。
		
```cpp
bool canJump(vector<int>& nums) 
{
    int n = nums.size();
    int rightmost = 0;
    for (int i = 0; i < n; ++i) {
        if (i <= rightmost) {
            rightmost = max(rightmost, i + nums[i]);
            if (rightmost >= n - 1) {
                return true;
            }
        }
    }
    return false;
}
```

## 二分查找
### 二分查找的前提
1. 目标函数单调性（单调递增或者递减）
2. 存在上下界
3. 能够通过索引访问

### 代码模板

```cpp
	int left = 0, right = nums.size() - 1;
	while(left <= right)
	{
		int mid = (left + right) / 2;
		if(nums[mid] == target
			return mid;
		else if(nums[mid] < target)
			left = mid + 1;
		else
			right = mid - 1;
	}
```
		实现int sqrt(int x) 函数
		
```cpp
int mySqrt(int x) 
{
    if(x < 2)
        return x;
    long left = 1, right = x;
    long mid = 1;
    while(left <= right)
    {
        mid = (left + right) / 2;
        if(mid * mid > x)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return (int)right;
}
```

```cpp
//牛顿迭代法
int mySqrt(int x) {
    long r = x;
    while( r * r > x)
        r = (r + x / r) / 2;
    return r;
}
```
			快速求平方根方法
```cpp
float InvSqrt(float x)
{
	float xhalf = 0.5f * x;
	int i = *(int*)&x;
	i = 0x5f3759df - (i >> 1);
	x = *(float*)&i;
	x = x * (1.5f - xhalf * x * x);
	return x;
}
```
			寻找旋转排序数组中的最小值
对于旋转数组的主要解题思路为，取中间值以后，该数组的左半和右半中必定有一个是顺序排列的，可以根据该特性来进行多一重的判定，再进行拆分。
```cpp
int findMin(vector<int>& nums) 
{
    if(nums.size() < 1)
        return -1;
    if (nums.size() == 1) 
        return nums[0];
    int left = 0, right = nums.size() - 1;
    if (nums[right] > nums[0]) 
        return nums[0];
    
    while (right >= left) 
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[mid + 1]) 
            return nums[mid + 1];
        if (nums[mid - 1] > nums[mid]) 
            return nums[mid];
        if (nums[mid] > nums[0]) 
            left = mid + 1;
        else 
            right = mid - 1;         
    }
    return -1;
}
```
			搜索旋转排序数组
```cpp
int search(vector<int>& nums, int target) 
{
    if(nums.size() < 1)
        return -1;
    int left = 0, right = nums.size() - 1;
    while(left <= right)
    {
        int mid = ((right + left + 1) >> 1);
        if(nums[mid] == target)
            return mid;
        if(nums[mid] > nums[left])
        { //如果左半边为顺序排列，那么判定目标是否在左半边之中
            if(nums[mid] < target || nums[left] > target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        else
        {//如果右半边为顺序排列，则判定目标是否在右半边之中
            if(nums[mid] > target || nums[right] < target)
                right = mid - 1;
            else
                left = mid + 1;
        }
    }
    return -1;
}
```