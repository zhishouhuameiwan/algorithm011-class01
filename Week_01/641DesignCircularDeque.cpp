/* 641. 设计循环双端队列
设计实现双端队列。
你的实现需要支持以下操作：

MyCircularDeque(k)：构造函数,双端队列的大小为k。
insertFront()：将一个元素添加到双端队列头部。 如果操作成功返回 true。
insertLast()：将一个元素添加到双端队列尾部。如果操作成功返回 true。
deleteFront()：从双端队列头部删除一个元素。 如果操作成功返回 true。
deleteLast()：从双端队列尾部删除一个元素。如果操作成功返回 true。
getFront()：从双端队列头部获得一个元素。如果双端队列为空，返回 -1。
getRear()：获得双端队列的最后一个元素。 如果双端队列为空，返回 -1。
isEmpty()：检查双端队列是否为空。
isFull()：检查双端队列是否满了。
示例：

MyCircularDeque circularDeque = new MycircularDeque(3); // 设置容量大小为3
circularDeque.insertLast(1);			        // 返回 true
circularDeque.insertLast(2);			        // 返回 true
circularDeque.insertFront(3);			        // 返回 true
circularDeque.insertFront(4);			        // 已经满了，返回 false
circularDeque.getRear();  				// 返回 2
circularDeque.isFull();				        // 返回 true
circularDeque.deleteLast();			        // 返回 true
circularDeque.insertFront(4);			        // 返回 true
circularDeque.getFront();				// 返回 4
 
 

提示：

所有值的范围为 [1, 1000]
操作次数的范围为 [1, 1000]
请不要使用内置的双端队列库 */

#include <iostream>
#include <vector>
using namespace std;

class MyCircularDeque {
    int size;
    vector<int> values;
public:
    /** Initialize your data structure here. Set the size of the deque to be k. */
    MyCircularDeque(int k) {
        size = k;
    }
    
    /** Adds an item at the front of Deque. Return true if the operation is successful. */
    bool insertFront(int value) {
        if(values.size() == size)
            return false;
        values.insert(values.begin(), value);
        return true;
    }
    
    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
    bool insertLast(int value) {
        if(values.size() == size)
            return false;
        values.push_back(value);
        return true;
    }
    
    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
    bool deleteFront() {
        if(values.size() > 0)
        {
            values.erase(values.begin());
            return true;
        }
        return false;
    }
    
    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
    bool deleteLast() {
        if(values.size() > 0)
        {
            values.pop_back();
            return true;
        }
        return false;
    }
    
    /** Get the front item from the deque. */
    int getFront() {
        if(values.size() > 0)
            return values.front();
        return -1;
    }
    
    /** Get the last item from the deque. */
    int getRear() {
        if(values.size() > 0)
            return values.back();
        return -1;
    }
    
    /** Checks whether the circular deque is empty or not. */
    bool isEmpty() {
        return values.empty();
    }
    
    /** Checks whether the circular deque is full or not. */
    bool isFull() {
        return values.size() == size;
    }
};


int main()
{
    MyCircularDeque* obj = new MyCircularDeque(3);
    bool param_1 = obj->insertFront(1);
    bool param_2 = obj->insertLast(2);
    bool param_3 = obj->insertLast(3);
    bool param_4 = obj->insertLast(4);
    bool param_5 = obj->deleteFront();
    bool param_6 = obj->deleteLast();
    int param_7 = obj->getFront();
    int param_8 = obj->getRear();
    bool param_9 = obj->isEmpty();
    bool param_10 = obj->isFull();

    //system("pause");
    return 0;
}