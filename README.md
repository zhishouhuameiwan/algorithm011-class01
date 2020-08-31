期末总结

# 数据结构
* 一维：
	* 基础：数组 vector(string)，链表 linked list
	* 高级：栈 stack，队列 queue，双端队列 deque，集合 set， 映射 map， 优先队列 priority_queue
* 二维：
	* 基础：树 tree， 图 graph
	* 高级： 二叉搜索树 binary search tree(red-black tree, AVL)，堆heap，并查集 disjoint set， 字典树 Trie
* 特殊：
	* 位运算 Bitwise， 布隆过滤器 BloomFilter
	* LRU Cache

# 时间复杂度
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200831184749358.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2wzNDYyNDI0OTg=,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200831185331477.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2wzNDYyNDI0OTg=,size_16,color_FFFFFF,t_70#pic_center)

# 算法
* if-else, switch -> branch
* for, while loop -> Iteration
* 递归 Recursion (Divide & Conquer, Backtrace)
* 搜索 Search：深度优先搜索 Depth first search，广度优先搜索 Breadth first search，A* 
* 动态规划 Dynamic Programming
* 二分查找 Binary Search
* 贪心 Greedy
* 数学 Math， 几何 Geometry

# 模板
* 递归
```cpp
void recursion(level, param1, param2, ...)
{
	//recursion terminator
	if(level > MAX_LEVEL)
	{
		process_result();
		return;
	}
	
	//process logic in current level
	process(level, data...);
	
	//drill down
	recursion(level + 1, p1, ...);
	
	//reverse the current level status if needed
}
```
* 分治

```cpp
void divide_conquer(problem, param1, param2, ...): 
  // recursion terminator 
  if problem is None: 
	print_result 
	return 
  // prepare data 
  data = prepare_data(problem) 
  subproblems = split_problem(problem, data) 
  // conquer subproblems 
  subresult1 = self.divide_conquer(subproblems[0], p1, ...) 
  subresult2 = self.divide_conquer(subproblems[1], p1, ...) 
  subresult3 = self.divide_conquer(subproblems[2], p1, ...) 
  …
  // process and generate the final result 
  result = process_result(subresult1, subresult2, subresult3, …)
	
  // revert the current level states

```
* DFS

```cpp
void dfs(Node* node, unordered_set<Node*>& visited)
{
	if(visited.count(node) > 0)
		return ;
	visited.insert(node);
	for(auto &child: node->children)
	{
		if(visited.count(child) < 1)
			dfs(child, visited);
	}
}
```
* BFS

```cpp
def bfs(graph, start, end)
{
	visited = set();
	queue = [];
	queue.append([start])
	
	while queue:
		node = queue.pop()
		visited.add(node)
		
		process(node)
		nodes = generate_related_nodes(node)
		queue.push(nodes)
}
```
* 归并排序

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
* 快速排序
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
* 堆排序
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

# 学习要点
* 基本功是区别业余和职业选手的根本。 深厚功底来自于--过遍数
* 最大的误区： 只做一遍
* 五毒神掌
* 刻意练习--练习缺陷弱点地方、不舒服、枯燥，但是这些都是成长的基础
* 反馈--看题解、看国际版的高票回答

# 经典习题
需要多次练习彻底掌握的习题：
爬楼梯、硬币兑换
括号生成、括号匹配、直方图最大面积、滑动窗口
二叉树遍历、分层输出树、判断二叉排序树
股票买卖、偷房子、字符串编辑距离、最长上升子序列、最长公共子序列
异位词（判断和归类）、回文串（最大回文串）、regex和通配符匹配
高级数据结构（Trie、BloomFilter、LRU cache）

# 五毒神掌
第一遍： 不要死磕，要看代码学习（一定要看国际版的高票回答）
第二遍：自己写
第三遍：24小时后
第四遍：一周后
第五遍：面试前

# 面试技巧
1. Clarfication：明确题目意思、边界、数据规模
2. Possible solutions：穷尽所有可能的解法
	- compare time 、space
	- optimal solution
3. Coding：代码简洁、高性能、美感
	[N皇后问题](https://shimo.im/docs/rHTyt8hcpT6D9Tj8/read)
4. Test cases

* N皇后位运算解法

```cpp
class Solution {
public:
    int totalNQueens(int n) {
        dfs(n, 0, 0, 0, 0);
        
        return this->res;
    }
    
    void dfs(int n, int row, int col, int ld, int rd) {
        if (row >= n) { res++; return; }
        
        // 将所有能放置 Q 的位置由 0 变成 1，以便进行后续的位遍历
        int bits = ~(col | ld | rd) & ((1 << n) - 1);
        while (bits > 0) {
            int pick = bits & -bits; // 注: x & -x
            dfs(n, row + 1, col | pick, (ld | pick) << 1, (rd | pick) >> 1);
            bits &= bits - 1; // 注: x & (x - 1)
        }
    }


private:
    int res = 0;
};
```


## 讲师课件下载地址

请大家通过该链接查看讲师课件并进行下载，课件链接:https://pan.baidu.com/s/1NBNdjXI0tjDzNKXf8fvaQQ  密码:kmxb

## 仓库目录结构说明

1. `week01/` 代表第一周作业提交目录，以此类推。
2. 请在对应周的目录下新建或修改自己的代码作业。
2. 每周均有一个 `REDAME.md` 文档，你可以将自己当周的学习心得以及做题过程中的思考记录在该文档中。

## 作业提交规则
 
1. 先将本仓库 Fork 到自己 GitHub 账号下。
2. 将 Fork 后的仓库 Clone 到本地，然后在本地仓库中对应周的目录下新建或修改自己的代码作业，当周的学习总结写在对应周的README.md文件里。
3. 在本地仓库完成作业后，push 到自己的 GitHub 远程仓库。
4. 最后将远程仓库中当周的作业链接，按格式贴到班级仓库对应学习周的issue下面。
5. 提交issue请务必按照规定格式进行提交，否则作业统计工具将抓取不到你的作业提交记录。 

详细的作业提交流程可以查阅：https://shimo.im/docs/m5rtM8K8rNsjw5jk/ 


## 注意事项

 如果对 Git 和 GitHub 不太了解，请参考 [Git 官方文档](https://git-scm.com/book/zh/v2) 或者极客时间的[《玩转 Git 三剑客》](https://time.geekbang.org/course/intro/145)视频课程。
