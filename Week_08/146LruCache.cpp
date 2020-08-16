//146. LRU缓存机制
#include <iostream>
#include <unordered_map>

struct STreeNode
{
    int val;
    int key;
    STreeNode *prev;
    STreeNode *next;
    STreeNode() : val(0) , key(0), prev(nullptr), next(nullptr){}
};


class LRUCache {
    int size;
    unordered_map<int, STreeNode*> mapCache;
    STreeNode *head;
    STreeNode *tail;

public:
    LRUCache(int capacity) {
        size = capacity;
        head = new STreeNode();
        tail = new STreeNode();
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if(mapCache.count(key) > 0)
        {
            STreeNode *node = mapCache[key];
            eraseNode(node);
            addHeadNode(node);
            return node->val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        STreeNode *node = nullptr;
        bool bErase = true;
        if(mapCache.count(key) > 0)
        {
            node = mapCache[key];
        }
        else
        {
            if(mapCache.size() == size)
            {
                node = tail->prev;
                mapCache.erase(node->key);
            }
            else
            {
                node = new STreeNode();
                bErase = false;
            }
        }
        node->key = key;
        node->val = value;
        if(bErase)
            eraseNode(node);
        addHeadNode(node);
        mapCache[key] = node;
    }

    void addHeadNode(STreeNode *node)
    {
        head->next->prev = node;
        node->next = head->next;
        node->prev = head;
        head->next = node;
    }

    void eraseNode(STreeNode *node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;      
    }
};
