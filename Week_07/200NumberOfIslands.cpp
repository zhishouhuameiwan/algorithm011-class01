//200岛屿数量

#include <iostream>
#include <vector>
using namespace std;

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


//  DFS
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