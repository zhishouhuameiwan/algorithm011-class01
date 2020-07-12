//二叉树的最近公共祖先

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
    unordered_map<int, TreeNode*> parentMap;
    unordered_map<int, int> vis;

public:
    void helper(TreeNode *root)
    {
        if(root == nullptr)
            return ;
        if(root->left)
        {
            parentMap[root->left->val] = root;
            helper(root->left);
        }
        if(root->right)
        {
            parentMap[root->right->val] = root;
            helper(root->right);
        }
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        parentMap[root->val] = nullptr;
        helper(root);
        TreeNode *tm = p;
        while(tm)
        {
            vis[tm->val] = 1;
            tm = parentMap[tm->val];
        }

        tm = q;
        while(tm)
        {
            if(vis[tm->val])
                return tm;
            tm = parentMap[tm->val];
        }
        return nullptr;
    }
};