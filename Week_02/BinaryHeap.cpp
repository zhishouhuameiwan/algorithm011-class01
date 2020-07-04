//二叉堆的实现
#include <iostream>
#include <vector>

using namespace std;

//二叉堆, 完全二叉树来实现的，所以可以使用数组来存放元素
class BinaryHeap
{
    int d = 2; //二叉树，定义最大子节点数为2
    vector<int> heap;
    int heapSize;

public:
    BinaryHeap(int capacity)
    {
        heapSize = 0;
        heap.resize(capacity + 1, -1);
    }

    //是否为空
    bool isEmpty()
    {
        return heapSize == 0;
    }

    //是否已满
    bool isFull()
    {
        return heapSize == heap.size();
    }

    //父节点下标
    int parent(int i)
    {
        return (i - 1) / d;
    }

    //子节点下标，k从1开始
    int kthChild(int i, int k)
    {
        return i * d + k;
    }

    //插入
    void insert(int val)
    {
        if(isFull())
        {
            cout << "Heap is full, No space to insert new element!" << endl;
            return ;
        }
        heap[heapSize++] = val;  //将插入的数值放入结尾，然后依次向上浮动
        heapifyUp(heapSize);  
    }

    //删除i为下标位置，返回删除的值
    int remove(int i = 0)
    {
        if(isEmpty())
        {
            cout << "Heap is empty, No element to remove!" << endl;
            return -1;
        }
        int removeElement = heap[i];  
        heap[i] = heap[--heapSize]; //将最后一个值放在删除的下标上，然后依次向下浮动
        heapifyDown(i);
        return removeElement;
    }

    //上浮
    void heapifyUp(int i)
    {
        int insertValue = heap[i];
        while(i > 0 && insertValue > heap[parent(i)])
        {
            heap[i] = heap[parent(i)];
            i = parent(i);
        }
        heap[i] = insertValue;
    }

    //下沉
    void heapifyDown(int i)
    {
        int child, temp = heap[i];
        while(kthChild(i, 1) < heapSize)
        {
            child = maxChild(i);
            if(temp >= heap[child])
                break;
            heap[i] = heap[child];
            i = child;
        }
        heap[i] = temp;
    }

    //最大子节点
    int maxChild(int i)
    {
        int leftChild = kthChild(i, 1);
        int rightChild = kthChild(i, 2);
        return heap[leftChild] > heap[rightChild] ? leftChild : rightChild;
    }

    //查找最大值
    int findMax()
    {
        if(isEmpty())
        {
            cout << "Heap is empty!" << endl;
            return -1;
        }
        return heap[0];
    }

    //打印堆
    void printHeap()
    {
        cout << "Heap = ";
        for(int i = 0; i < heapSize; i++)
            cout << heap[i] << " ";
        cout << endl;
    }
};

int main()
{
    BinaryHeap maxHeap(10);
    maxHeap.insert(10);
    maxHeap.insert(4);
    maxHeap.insert(9);
    maxHeap.insert(1);
    maxHeap.insert(7);
    maxHeap.insert(5);
    maxHeap.insert(3);


    maxHeap.printHeap();
    maxHeap.remove(5);
    maxHeap.printHeap();
    maxHeap.remove(0);
    maxHeap.printHeap();

    system("pause");
    return 0;
}