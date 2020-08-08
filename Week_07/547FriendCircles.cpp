//547 朋友圈

#include <iostream>
#include <vector>
using namespace std;

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