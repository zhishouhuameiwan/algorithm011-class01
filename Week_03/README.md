学习笔记
分治
分治和回溯本身就是一种比较特殊的递归，在分析问题的解决方法时候，首先找问题的重复性，某些情况下，问题可能需要拆分成多个小问题来实现，然后最后结果是多个小问题组合起来形成的，这时候就需要用到分治的思想。
分治类似公司自顶而下管理和工作的架构，分析问题，拆分子问题的方法主要是多加练习，根据解题的经验来进行拆分和组合。

分治的代码模板

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
  
  回溯
回溯法采用试错的思想，它尝试分步的去解决一个问题。在分布解决问题的过程中，当它通过尝试发现现有的分步答案不能得到有效的正确的解答的时候，他将取消上一步甚至是上几步的计算，再通过其他可能的分步解答再次尝试寻找问题的答案。
回溯法通常用最简单的递归方法来实现，在反复重复上述步骤后可能出现两种情况：

找到一个可能存在的正确的答案。

尝试了所有可能的分步方法后宣告该问题没有答案。
在最坏的情况下，回溯法会导致依次复杂度为指数时间的计算。
最典型的应用是在八皇后以及数独的问题解决方案上。
回溯算法要简化，进行及时的剪枝处理可以大大减少算法的运行时间。


	给定一个可包含重复数字的序列，返回所有不重复的全排列。

vector<vector<int>> res;
    vector<int> mNums;
    vector<int> list;
    vector<int> used;
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        mNums = nums;
        used.resize(nums.size(), 0);
        helper();
        return std::move(res);
    }

    void helper()
    {
        if(list.size() == mNums.size())
        {
            res.push_back(list);
            return ;
        }
        for(int i = 0; i < mNums.size(); i++)
        {
            if(used[i] || (i > 0 && (used[i - 1] == 0) && mNums[i] == mNums[i -1]))
                continue;

            used[i] = 1;
            list.push_back(mNums[i]);
            helper();
            list.pop_back();
            used[i] = 0;
        }
    }

	从前序与中序遍历序列构造二叉树

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.size() < 1)
            return nullptr;
        unordered_map<int, int> inMap;
        for(int i = 0; i < inorder.size(); i++)
            inMap[inorder[i]] = i;
        return helper(preorder, inMap, 0, preorder.size() - 1, 0, inorder.size() - 1);
    }

    TreeNode* helper(vector<int>& preorder, unordered_map<int, int>& inMap, int preStart, int preEnd, int inStart, int inEnd)
    {
        if(preStart > preEnd || inStart > inEnd)
            return nullptr;      
        TreeNode * node = new TreeNode(preorder[preStart]);
        if(preStart == preEnd)
            return node;
        int index = inMap[preorder[preStart]];
        node->left = helper(preorder, inMap, preStart + 1, preStart + index - inStart, inStart, index - 1);
        node->right = helper(preorder, inMap, preEnd - inEnd + index + 1, preEnd, index + 1, inEnd);
        return node;
    }
};
