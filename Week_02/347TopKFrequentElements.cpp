//给定一个非空的整数数组，返回其中出现频率前 k 高的元素。

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;


class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> res;
        unordered_map<int, int> mp;
        for(int &n : nums)
            mp[n]++;
        priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> qu;
        for(auto it = mp.begin(); it != mp.end(); it++)
        {
            qu.push(pair(it->second, it->first));
            if(qu.size() > k)
                qu.pop();
        }
        while(!qu.empty())
        {
            res.push_back(qu.top().second);
            qu.pop();
        }
        return std::move(res);
    }
};