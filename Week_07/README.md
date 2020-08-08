学习笔记

# 字典树和并查集
## 字典树
字典树，即Trie树，又称单词查找树或者键树，是一种树形结构。典型应用是用于统计或者排序大量的字符串（但不仅限于字符串），所以经常被搜索引擎系统用于文本词频统计，或者屏蔽词字库对比等。
字典树优点：最大限度的减少无畏的字符串比较，查询效率比哈希表高。
Trie树的核心思想是空间换时间。
利用字符串的公共前缀来降低查询时间的开销以达到提高效率的目的。
==字典树的实现==
```cpp
struct Node
{
    char c;
    bool end;
    Node* next[26] = {};

    Node(char ca, bool end_) : c(ca), end(end_) {}
   // Node(char ca, bool end_, int nextc) : c(ca), end(end_){ next[nextc] = 1;}
};

class Trie {
    Node *root;
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new Node('0', false);
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Node *node = root;
        int i = -1;
        while(++i < word.size())
        {
            int t = word[i] - 'a';
            if(node->next[t])
                node = node->next[t];
            else
            {
                node->next[t] = new Node(word[i], false);
                node = node->next[t];
            }
        }
        node->end = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Node *node = root;
        int i = -1;
        while(++i < word.size())
        {
            int t = word[i] - 'a';
            if(node->next[t])
                node = node->next[t];
            else
                return false;
        }
        return node->end;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Node *node = root;
        int i = -1;
        while(++i < prefix.size())
        {
            int t = prefix[i] - 'a';
            if(node->next[t])
                node = node->next[t];
            else
                return false;
        }
        return true;
    }
};

```
## 并查集
并查集主要用于解决组团、配对问题，判定是否为一个组。

### 并查集的基本操作
·makeSet(s)： 建立一个新的并查集，其中包含s个单元素集合。
·unionSet(x, y)：把元素x和元素y所在的集合合并，要求x和y所在的集合不相交，如果相交则不合并。
·find(x)：找到元素x所在的集合的代表，该操作也可以用于判定两个元素是否位于同一个集合，只要将他们各自的代表比较一下就可以了。
==朋友圈问题==

```cpp
//班上有 N 名学生。其中有些人是朋友，有些则不是。他们的友谊具有是传递性。如果已知 A 是 B 的朋友，B 是 C 的朋友，那么我们可以认为 A 也是 C 的朋友。所谓的朋友圈，是指所有朋友的集合。

//给定一个 N * N 的矩阵 M，表示班级中学生之间的朋友关系。如果M[i][j] = 1，表示已知第 i 个和 j 个学生互为朋友关系，否则为不知道。你必须输出所有学生中的已知的朋友圈总数。

class Solution {
    vector<int> parent;
    int count;
public:
    void initUnionFind(int n)
    {
        parent.resize(n);
        for(int i = 0; i < n; i++)
            parent[i] = i;
        count  = n;
    }

    int find(int x)
    {
        if(x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if(rootX != rootY)
        {
            parent[rootY] = rootX;
            count--;
        }         
    }

    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size();
        initUnionFind(n);
        for(int i = 0; i < n; i++)
        {
            for(int j = i + 1; j < n; j++)
            {
                if(M[i][j] == 1)
                    unite(i, j);
            }
        }
        return count;
    }
};
```
==岛屿数量问题==

```cpp
//并查集
class UnionFind{
private:
    int count;
    vector<int> parent;

public:
    UnionFind(vector<vector<char>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        count  = 0;
        parent.resize(m * n, -1);
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(grid[i][j] == '1')
                {
                    parent[i * n + j] = i * n + j;
                    count++;
                }
            }
        }    
    }

    int find(int i)
    {
        while(i != parent[i])
        {
            int p = parent[i];
            parent[i] = parent[p];
            i = p;
        }
        return parent[i];
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if(rootX != rootY)
        {
            parent[rootY] = rootX;
            count--;
        }   
    }

    int getCount() const { return count;}

};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.size() < 1 || grid[0].size() < 1)
            return 0;
        int m = grid.size(), n = grid[0].size();
        UnionFind uf(grid);
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(grid[i][j] == '1')
                {
                    if(i + 1 < m && grid[i + 1][j] == '1')
                        uf.unite(i * n + j, (i + 1) * n + j);
                    if(j + 1 < n && grid[i][j + 1] == '1')
                        uf.unite(i * n + j, i * n + j + 1);
                }
            }
        }
        return uf.getCount();
    }
};
```
==用DFS解决岛屿数量问题==
```cpp
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.size() < 1 || grid[0].size() < 1)
            return 0;
        int res = 0;
        for(int i = 0; i < grid.size(); i++)
        {
            for(int j = 0; j < grid[0].size(); j++)
            {
                if(grid[i][j] == '1')
                {
                    helper(grid, i, j);
                    res++;
                }            
            }
        }
        return res;
    }

    void helper(vector<vector<char>>& grid, int i, int j)
    {
        if(i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size())
            return ;

        grid[i][j] = '0';
        if(i > 0 && grid[i - 1][j] == '1')
            helper(grid, i - 1, j);
        if(j > 0 && grid[i][j - 1] == '1')
            helper(grid, i, j - 1);
        if(i < grid.size() - 1 && grid[i + 1][j] == '1')
            helper(grid, i + 1, j);
        if(j < grid[0].size() - 1 && grid[i][j + 1] == '1')
            helper(grid, i, j + 1);
    }
};
```
# 高级搜索
## 剪枝
初级搜索包含
1. 朴素搜索
2. 优化方式：不重复（Fibonacci）、剪枝（生成括号问题）
3. 搜素方向：
	DFS：depth first search 深度优先搜索
	BFS：breadth first search 广度优先搜索
	双向搜索、启发式搜素

==有效的数独==

```cpp
bool isValidSudoku(vector<vector<char>>& board) {
        int R[9][9] = {};//row
        int C[9][9] = {};//col
        int B[9][9] = {};//block
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    if (R[i][board[i][j] - '0']++) 
                    	return false;
                    if (C[j][board[i][j] - '0']++) 
                    	return false;
                    if (B[(i / 3) * 3 + (j / 3)][board[i][j] - '0']++)
                    	return false;
                }
            }
        }
        return true;  
    } 
```
## 双向BFS
双向BFS其实就是从首尾两端同时进行BFS，每次选取最优的端来进行查找，这样可以起到优化的作用。

==单词接龙==
```cpp
//给定两个单词（beginWord 和 endWord）和一个字典，找到从 beginWord 到 endWord 的最短转换序列的长度。转换需遵循如下规则：
//每次转换只能改变一个字母。
//转换过程中的中间单词必须是字典中的单词。

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if(dict.find(endWord) == dict.end())
            return 0;
        unordered_set<string> beginSet, endSet, tm, visited;
        beginSet.insert(beginWord);
        endSet.insert(endWord);
        int len = 1;

        while(!beginSet.empty() && !endSet.empty())
        {
            if(beginSet.size() > endSet.size())
            {
                tm = beginSet;
                beginSet = endSet;
                endSet = tm;
            }

            tm.clear();
            for(string word : beginSet)
            {    
                for(int i = 0; i < word.size(); i++)
                {
                    char old = word[i];
                    for(char c = 'a'; c <= 'z'; c++)
                    {
                        if(old == c)
                            continue;
                        word[i] = c;
                        if(endSet.find(word) != endSet.end())
                            return len + 1;
                        if(visited.find(word) == visited.end() && dict.find(word) != dict.end())
                        {
                            tm.insert(word);
                            visited.insert(word);
                        }
                    }
                    word[i] = old;
                }
            }
            beginSet = tm;
            len++;
        }
        return 0;
    }
};
```
## 启发式搜索
启发式搜索就是根据估价函数每次从最优的节点进行搜索，来减少搜索次数以达到目标。
### 估价函数
启发式函数：h(n)，它用来评价哪些节点最有希望的是一个我们要找的结点，h(n)会返回一个非负实数，也可以认为是从节点n的目标结点路径的估计成本。
启发式函数是一种告知搜索方向的方法，它提供了一种明智的方法来猜测哪个邻居节点会导向一个目标。
常用的估价函数：
曼哈顿距离: Manhattan distance = |x1 - x2| + |y1 - y2|



==A*的算法模板==

```cpp
C/C++
class Node {
public:
    int x;
    int y;
    bool operator< (const Node &A) {
        // 
    }
};

void generate_related_nodes(Node &node) {
    // 
}

void process(Node &node) {
    // 
}

void AstarSearch(vector<vector<int>>& graph, Node& start, Node& end) {
    vector<vector<bool> > visited(graph.size(), vector<bool>(graph[0].size(), false));
    priority_queue<Node> q;
    q.push(start);

    while (!q.empty()) {
        Node cur = q.top();
        q.pop();
        visited[cur.x][cur.y] = true;
        
        process(node);
        vector<Node> nodes = generate_related_nodes(node) 
        for (auto node : nodes) {
            if (!visited[node.x][node.y]) q.push(node);
        }
    }
    return ;
}
```

# AVL树和红黑树
## AVL树
1. AVL 树名字的由来是由发明者 G.M.Adelson-Velsky和Evgenii Landis的名字首字母来的。
2. 平衡二叉搜索树。
3. Balance Factor（平衡因子）
	是它的左子树高度减去它的右子树高度（有时相反）。
	balance factor = {-1, 0, 1};
	保证高度差在-1到1之间
4. 通过旋转操作来进行平衡（左旋，右旋，左右旋，右左旋）
5. 缺点是：结点需要存储额外信息，且调整次数频繁
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808225217539.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2wzNDYyNDI0OTg=,size_16,color_FFFFFF,t_70)
## 红黑树
红黑树是一种近似平衡的二叉搜索树，它能够确保任何一个节点的左右子树的==高度差小于两倍==。具体来说，红黑树是满足如下条件的二叉搜索树：
1. 每个节点要么是红色，要么是黑色。
2. 根节点是黑色。
3. 每个叶节点（NIL节点 ，空节点）是黑色的。
4. 不能有相邻接的两个红色结点
5. 从任一结点到其每个叶子的所有路径都包含相同数目的黑色结点。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200808225717315.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2wzNDYyNDI0OTg=,size_16,color_FFFFFF,t_70)
## AVL树与红黑树对比：
1. AVL trees provide ==faster lookups== than RedBlack Trees because they are more strictly balanced.
2. RedBlack Trees provide ==faster insertion and removal== operations than AVL trees as fewer rotations are done due to relatiively relaxed balancing.
3. AVL trees store balance ==factors or heights== with each node, thus requires storage for an integer per node whereas Red Black Tree requires only ==1 bit== of information per node.
4. Red Black trees are used in most of the ==language libraries like map, multimap, multiset in C++== where AVL trees are used in ==databases== where faster retrievals are required.
