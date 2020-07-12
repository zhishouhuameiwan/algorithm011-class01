//从前序与中序遍历序列构造二叉树

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

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

int main()
{
    vector<int> preorder = {1, 2};
    vector<int> inorder = {2, 1};
    Solution so;
    so.buildTree(preorder, inorder);
    return 0;
}