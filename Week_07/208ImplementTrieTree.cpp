//208. 实现 Trie (前缀树)

#include <iostream>
#include <vector>
#include <string>
using namespace std;

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

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */