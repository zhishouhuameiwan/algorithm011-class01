学习笔记
# 位运算
## 位运算符
含义 |  运算符 | 说明
-------|-----------|---------
按位或 |  1 | 双目，只要有一个为1则为1，否则为0
按位与| &| 双目，两个都为1则为1，否则为0
按位取反| ~ | 单目， 每位0变1，1变0
按位异或| ^ | 双目，相同为0，不同为1

### 异或特点
相同为0， 不同为1，也可用“不进位加法”来理解。
x ^ 0 = x
x ^ 1s = ~x   //注意 1s = ~0 相当于每位都为1
x ^ (~x) = 1s 
x ^ x = 0
c = a ^ b => a ^ c = b , b ^ c = a   //交换两个数   经常用于密码学
a ^ b ^ c = a ^ (b ^ c) = (a ^ b) ^ c  //associative

### 指定位置的位运算
1. 将x的最右边的n位清零： x & (~0 << n)
2. 获取x的第n位值（0或者1）： (x >> n) & 1
3. 获取x的第n位的幂值： x & (1 << n)
4. 仅将第n位置为1： x | (1 << n)
5. 仅将第n位置为0： x & (~(1 << n))
6. 将x的最高位至第n位清零： x & ((1 << n) - 1)
7. 将x的最后一个1置为0 ： x & (x - 1)   //经常用于判定汉明重量，以及x是否为2的次幂

### 实战位运算要点
1. 判断奇偶
	x % 2 == 1   ==>   (x & 1) == 1
	x % 2 == 0   ==>   (x & 1) == 0  
2. x >> 1    ⇒  x / 2
3.  x & -x ==> 得到最低为的1
4. x & ~ x ⇒ 0

==给定一个整数，编写一个函数来判断它是否是 2 的幂次方==

```cpp
bool isPowerOfTwo(int n) {
    return n > 0 ?  (n & n - 1) == 0 : false;
}
```
==编写一个函数，输入是一个无符号整数，返回其二进制表达式中数字位数为 ‘1’ 的个数（也被称为汉明重量）。==

```cpp
int hammingWeight(uint32_t n) {
    int count  = 0;
    while(n != 0)
    {
        n &= (n - 1);
        count++;
    }
    return count;
}
```

==颠倒给定的 32 位无符号整数的二进制位。==

```cpp
uint32_t reverseBits(uint32_t n) {
    uint32_t res = 0, step = 31;
    while(n != 0)
    {
        res += ((n & 1) << (step--));
        n = (n >> 1);
    }
    return res;
}
```
# 布隆过滤器
## 布隆过滤器介绍
1. 巴顿.布隆于一九七零年提出
2. 一个很长的二进制向量 （位数组）
3. 一系列随机函数 (哈希)
4. 空间效率和查询效率高
5. 有一定的误判率（哈希表是精确匹配）

## Bloom Filter vs Hash Table
一个很长的二进制向量和一系列随机映射函数。布隆过滤器可以用于检测一个元素是否在一个集合中。
优点是 空间效率和查询时间都远远超过一般的算法。
缺点是 有一定的误识别率和删除困难。
==布隆过滤器仅用于量级较大的查询，用于快速的过滤掉一部分数据。==


## 布隆过滤器原理
布隆过滤器（Bloom Filter）的核心实现是一个超大的位数组和几个哈希函数。假设位数组的长度为m，哈希函数的个数为k
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200816211957403.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2wzNDYyNDI0OTg=,size_16,color_FFFFFF,t_70#pic_center)
以上图为例，具体的操作流程：假设集合里面有3个元素{x, y, z}，哈希函数的个数为3。首先将位数组进行初始化，将里面每个位都设置位0。对于集合里面的每一个元素，将元素依次通过3个哈希函数进行映射，每次映射都会产生一个哈希值，这个值对应位数组上面的一个点，然后将位数组对应的位置标记为1。查询W元素是否存在集合中的时候，同样的方法将W通过哈希映射到位数组上的3个点。如果3个点的其中有一个点不为1，则可以判断该元素一定不存在集合中。反之，如果3个点都为1，则该元素可能存在集合中。注意：此处不能判断该元素是否一定存在集合中，可能存在一定的误判率。可以从图中可以看到：假设某个元素通过映射对应下标为4，5，6这3个点。虽然这3个点都为1，但是很明显这3个点是不同元素经过哈希得到的位置，因此这种情况说明元素虽然不在集合中，也可能对应的都是1，这是误判率存在的原因。

## 布隆过滤器添加元素
将要添加的元素给k个哈希函数
得到对应于位数组上的k个位置
将这k个位置设为1
## 布隆过滤器查询元素
将要查询的元素给k个哈希函数
得到对应于位数组上的k个位置
==如果k个位置有一个为0，则肯定不在集合中==
==如果k个位置全部为1，则可能在集合中==

## 案例
1. 比特币网络
2. 分布式系统（Map-Reduce）- hadoop 、 search engine
3. Redis缓存
4. 垃圾邮件，评论等的过滤

## 使用原理
现在布隆过滤器器中查询该元素是否存在，如果不在，则肯定不存在，不需要继续往下进行。如果存在，则可能存在集合中，需要进一步下探到数据库或者hash等准确的位置进行查询定位。
使用该特性可以过滤掉大部分信息。

# LRU Cache
1. 两个要素： 大小、替换策略
2. Hash Table + Double LinkedList
3. O(1) 查询
	O(1) 修改、更新
	

```cpp
struct STreeNode
{
    int val;
    int key;
    STreeNode *prev;
    STreeNode *next;
    STreeNode() : val(0) , key(0), prev(nullptr), next(nullptr){}
};


class LRUCache {
    int size;
    unordered_map<int, STreeNode*> mapCache;
    STreeNode *head;
    STreeNode *tail;

public:
    LRUCache(int capacity) {
        size = capacity;
        head = new STreeNode();
        tail = new STreeNode();
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if(mapCache.count(key) > 0)
        {
            STreeNode *node = mapCache[key];
            eraseNode(node);
            addHeadNode(node);
            return node->val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        STreeNode *node = nullptr;
        bool bErase = true;
        if(mapCache.count(key) > 0)
        {
            node = mapCache[key];
        }
        else
        {
            if(mapCache.size() == size)
            {
                node = tail->prev;
                mapCache.erase(node->key);
            }
            else
            {
                node = new STreeNode();
                bErase = false;
            }
        }
        node->key = key;
        node->val = value;
        if(bErase)
            eraseNode(node);
        addHeadNode(node);
        mapCache[key] = node;
    }

    void addHeadNode(STreeNode *node)
    {
        head->next->prev = node;
        node->next = head->next;
        node->prev = head;
        head->next = node;
    }

    void eraseNode(STreeNode *node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;      
    }
};
```
# 排序算法
1. 比较类排序：
	通过比较来决定元素间的相对次序，由于其时间的复杂度不能突破O(nlogn)，因此也称为非线性时间比较类排序。
2. 非比较类排序：
	不通过比较来决定元素间的相对次序，它可以突破基于比较排序的时间下界，以线性时间运行，因此也称为线性时间非比较类排序。
	![在这里插入图片描述](https://img-blog.csdnimg.cn/20200816213447105.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2wzNDYyNDI0OTg=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200816213454171.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2wzNDYyNDI0OTg=,size_16,color_FFFFFF,t_70#pic_center)
这里推荐大佬的博客[十大经典排序算法](https://www.cnblogs.com/onepixel/p/7674659.html)

## 初级排序 -- O(N ^ 2)
1. 选择排序（Selection Sort）
	每次找最小值，然后放到待排序数据的起始位置。
2. 插入排序 （Insertion Sort）
	从前到后逐步构建有序序列，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。
3. 冒泡排序（Bubble Sort）
	嵌套循环，每次查看相邻的元素，如果逆序，则交换。
## 高级排序 -- O(N * LogN)
1. 快速排序（Quick Sort）
	数组取标杆pivot，将小元素放pivot左边，大元素放右边，然后一次对左边和右边的子数组继续快排，以达到整个序列有序。
	
```cpp
void quickSort(vector<int>& nums, int begin, int end)
{
	if(begin > end)
		return ;
	int pivot = partition(nums, begin, end);
	quickSort(nums, begin, pivot - 1);
	quickSort(nums, pivot + 1, end);
}
int partition(vector<int>& nums, int begin, int end)
{
	int pivot = end, counter = begin;
	for(int i = begin, i < end; i++)
	{
		if(nums[i] < nums[pivot])
			swap(nums[counter++], nums[i]);
	}
	swap(nums[counter], nums[pivot]);
	return counter;
}

```
2. 归并排序（Merge Sort）-- 分治
	把长度位n的输入序列分为两个长度位n/2的子序列；
	对这两个子序列分别采用归并排序；
	将两个排序好的子序列合并成一个最终的排序序列。

```cpp
void mergeSort(vector<int>& nums, int left, int right)
{
	if(left > right)
		return;
	int mid = ((left + right) >> 1);
	mergeSort(nums, left, mid);
	mergeSort(nums, mid + 1, right);
	merge(nums, left, mid, right);
}

void merge(vector<int>& nums, int left, int mid, int right)
{
	vector<int> temp(right - left + 1);
	int i = left, j = mid + 1, k = 0;
	while(i <= mid && j <= right)
		temp[k++] = nums[i] <= nums[j] ? nums[i++] : nums[j++];
	while(i <= mid) temp[k++] = nums[i++]; //如果左侧数组没用完
	while(j <= right) temp[k++] = nums[j++]; //如果右侧数组没用完
	for(int p = 0; p < temp.size(); p++)
		nums[left + p] = temp[p];
}

```
归并和快排具有相似性，但是步骤顺序相反
归并：先排序左右子数组，然后合并两个有序子数组。
快排：先调配出左右子数组 ，然后对于左右子数组进行排序。

3. 堆排序（Heap Sort）--堆插入O(logN)，取最大/小值O(1)
	数组元素依次建立小顶堆
	依次取堆顶元素，并删除
	

```cpp
void heapSort(vector<int>& nums)
{
	priority_queue<int, vector<int>, greater<int>> pq;
	for(int i = 0; i < nums.size(); i++)
		pq.push(nums[i]);
	for(int i = 0; i < nums.size(); i++)
		nums[i] = pq.pop();
}
```

```cpp
void heapify(vector<int>& nums, int length, int i)
{
	int left = 2 * i + 1, right = 2 * i + 2;
	int largest = i;
	if(left < length && nums[left] > nums[largest])
		largest = left;
	if(right < length && nums[right] > nums[largest])
		largest = right;
	if(largest != i)
	{
		swap(nums[i], nums[largest]);
		heapify(nums, largest);
	}	
}
void heapSort(vector<int>& nums)
{
	if(nums.size() < 1)
		return;
	int length = nums.size();
	for(int i = length / 2 - 1; i >= 0; i--)
		heapify(nums, length, i);
	for(int i = length - 1; i >= 0; i--)
	{
		swap(nums[0], nums[i]);
		heapify(nums, i, 0);
	}
}
```
== 翻转对 给定一个数组 nums ，如果 i < j 且 nums[i] > 2*nums[j] 我们就将 (i, j) 称作一个重要翻转对。你需要返回给定数组中的重要翻转对的数量。==

```cpp
void merge(vector<int>& A, int start, int mid, int end)
{
    int n1 = (mid - start + 1);
    int n2 = (end - mid);
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = A[start + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[mid + 1 + j];
    int i = 0, j = 0;
    for (int k = start; k <= end; k++) {
        if (j >= n2 || (i < n1 && L[i] <= R[j]))
            A[k] = L[i++];
        else
            A[k] = R[j++];
    }
}

int mergesort_and_count(vector<int>& A, int start, int end)
{
    if (start < end) {
        int mid = (start + end) / 2;
        int count = mergesort_and_count(A, start, mid) + mergesort_and_count(A, mid + 1, end);
        int j = mid + 1;
        for (int i = start; i <= mid; i++) {
            while (j <= end && A[i] > A[j] * 2LL)
                j++;
            count += j - (mid + 1);
        }
        merge(A, start, mid, end);
        return count;
    }
    else
        return 0;
}

int reversePairs(vector<int>& nums)
{
    return mergesort_and_count(nums, 0, nums.size() - 1);
}

```
