Hash、树、堆
本周主要学习了hashmap，映射，集合，树，heap以及图相关的基础知识，以及对应的相关算法。

HashMap
关于hash的主要内容：
1. Hash表是根据关键码值（key）进行直接访问的数据结构，通过hash函数把key映射到表中一个位置来进行访问，查找元素的时间复杂度为O(1)。
2. hash映射函数也叫散列函数，存放记录的数组叫做哈希表。
3. hash表的做法，就是把key值通过设定的hash函数转换成一个int数字，然后将该数字对数组长度进行取余，取余结果即为数组的下标，然后将value的值存储在数组的该位置。如果hash值相同或者取余结果相同时候，通过拉链模式来存储多个元素，即该位置为链表的root节点，往下依次遍历数值来确定key的准确位置。一般来说拉链模式最大长度为8，因为该模式下，hash的时间复杂度退化到O(k)，k为该位置链表长度，所以一个好的hash函数尽量避免重复的hash key值显得尤为重要。


树
树作为一种非常常见的二维数据结构，从子节点数量可以分为二叉树，N叉树等，从使用特点上分为二叉搜索树，红黑树等。
树的定义本身没法有效的进行所谓的循环，而且树对于父节点与子节点处理方式基本一致，所以树一般使用递归算法来进行实现。
二叉搜索树也叫二叉排序树，指二叉树每个节点的左子树上的所有节点的值均小于该节点的值，右子树上的所有节点值均大于该节点的值。因为二叉搜索树的有序性，在查找，添加，删除等方面基本都为O(logN)的时间复杂度。中序遍历为升序排列。
关于二叉树的前中后遍历，使用栈的实现
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

Heap
Heap 可以迅速的找到一堆数中的最大值或者最小值的数据结构。
将根节点最大的堆叫做大顶堆或者大根堆，根节点最小的堆叫做最小顶堆或者小根堆，常见的堆有二叉堆、斐波那契堆等。
C++中基本的堆数据结构为优先队列priority_queue，初始化方法如下
priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> qu; //以第一个int排序，为大根堆
priority_queue<int, vector<int>, std::less<int>> qu; //int类型小根堆
priority_queue<int> qu;  //int类型小根堆
