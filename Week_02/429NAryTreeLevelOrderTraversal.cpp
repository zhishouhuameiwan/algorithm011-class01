//N叉树的层序遍历

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};


class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> res;
        if(root)
        {
            vector<int> level;
            queue<Node*> qu;
            Node *last = root;
            qu.push(root);
            while(!qu.empty())
            {
                Node *node = qu.front();
                qu.pop();
                level.push_back(node->val);
                for(int i = 0; i < node->children.size(); i++)
                {
                    qu.push(node->children[i]);
                }
                if(node == last)
                {
                    last = qu.back();
                    res.push_back(level);
                    level.clear();
                }       
            }
        }
        return std::move(res);
    }
};

