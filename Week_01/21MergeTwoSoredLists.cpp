/* 21. 合并两个有序链表
将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

 

示例：

输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4 */

#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


//简易链表管理
class ListNodeManager
{
public:
    //生成链表
    ListNode *Create(vector<int> &vec)
    {
        ListNode *head = nullptr, *prev = nullptr;
        for (int i = 0; i < vec.size(); i++)
        {
            ListNode *node = new ListNode();
            node->val = vec[i];
            if(!head)
                head = node;
            if(prev)
                prev->next = node;
            prev = node;
        }
        return head;
    };

    //打印链表
    void Print(ListNode *head)
    {
        ListNode *node = head;
        while(node)
        {
            cout << node->val << " ";
            node = node->next;
        }
        cout << endl;
    }

    //清空
    void Clear(ListNode *head)
    {
        ListNode *node = head, *next = nullptr;
        while(node)
        {
            next = node->next;
            delete node;
            node = next;
        }
    }
};



class Solution {
public:
    //使用vec数组缓存
    ListNode* mergeTwoLists_A(ListNode* l1, ListNode* l2) {
        ListNode *head = nullptr;
        ListNode *node1 = l1, *node2 = l2;
        vector<ListNode *> vec;
        while(node1 || node2)
        {
            if(node1 && (!node2 || node1->val <= node2->val))
            {
                vec.push_back(node1);
                node1 = node1->next;
            }
            if(node2 && (!node1 || node1->val > node2->val))
            {
                vec.push_back(node2);
                node2 = node2->next;
            }
        }
        if(vec.size() < 1)
            return head;
        for (int i = 0; i < vec.size() - 1; i++)
        {
            vec[i]->next = vec[i + 1];
        }

        head = vec[0];
        vec[vec.size() - 1]->next = nullptr;     
        return head;
    }

    //递归
    ListNode* mergeTwoLists_B(ListNode* l1, ListNode* l2) {
        if(!l1)
            return l2;
        if(!l2)
            return l1;
        if(l1->val < l2->val)
        {
            l1->next = mergeTwoLists_B(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next = mergeTwoLists_B(l1, l2->next);
            return l2;
        }
    }

    //迭代
    ListNode* mergeTwoLists_C(ListNode* l1, ListNode* l2) {
        ListNode *preHead = new ListNode(-1);
        ListNode *node = preHead;
        while(l1 && l2)
        {
            if(l1->val <= l2->val)
            {
                node->next = l1;
                l1 = l1->next;
            }
            else
            {
                node->next = l2;
                l2 = l2->next;
            }
            node = node->next;
        }
        node->next = l1 == nullptr ? l2 : l1;
        return preHead->next;
    }
};



int main()
{
    ListNodeManager mg;
    vector<int> nums1 = {1, 2, 4};
    vector<int> nums2 = {1, 3, 4};

    ListNode *l1 = mg.Create(nums1);
    mg.Print(l1);

    ListNode *l2 = mg.Create(nums2);
    mg.Print(l2);

    Solution so;
    //ListNode *head = so.mergeTwoLists_A(l1, l2);
    //ListNode *head = so.mergeTwoLists_B(l1, l2);
    ListNode *head = so.mergeTwoLists_C(l1, l2);

    mg.Print(head);

    system("pause");

    return 0;
}