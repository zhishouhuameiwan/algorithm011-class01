//二叉树的遍历
#include <iostream>
#include <stack>
#include <vector>
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
    //前序遍历
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        if(root)
        {
            stack<TreeNode *> st;
            st.push(root);
            while(!st.empty())
            {
                TreeNode *node = st.top();
                st.pop();
                if(node)
                {
                    res.push_back(node->val);
                    if(node->right)
                        st.push(node->right);
                    if(node->left)
                        st.push(node->left);
                }
            }
        }
        return res;
    }

    //中序遍历
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if(root)
        {
            stack<TreeNode *> st;
            st.push(root);
            while(!st.empty())
            {
                TreeNode *node = st.top();
                st.pop();
                if(node)
                {
                    if(node->right)
                        st.push(node->right);
                    st.push(node);
                    st.push(nullptr);
                    if(node->left)
                        st.push(node->left);
                }
                else
                {
                    res.push_back(st.top()->val);
                    st.pop();
                }
            }
        }
        return res;
    }

    //后续遍历
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if(root)
        {
            stack<TreeNode *> st;
            st.push(root);
            while(!st.empty())
            {
                TreeNode *node = st.top();
                st.pop();
                if(node)
                {
                    st.push(node);
                    st.push(nullptr);
                    if(node->right)
                        st.push(node->right);
                    if(node->left)
                        st.push(node->left);
                }
                else
                {
                    res.push_back(st.top()->val);
                    st.pop();
                }
            }
        }
        return res;
    }
};

