
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct PriorityQueue
{
private:
    //stores values
    vector<int> MaxHeap;
    int Parent(int i) 
    {
        return (i - 1) / 2;
    }

    //returns left child
    int LC(int i) 
    {
        return (2 * i + 1);
    }

    //returns right child
    int RC(int i) 
    {
        return (2 * i + 2);
    }


    //Heapify's up
    void heapifyU(int x)
    {
        // Checks if swap is neccessary
        if (MaxHeap[Parent(x)] < MaxHeap[x])
        {
            swap(MaxHeap[x], MaxHeap[Parent(x)]);
            //calls Heapifyu again
            heapifyU(Parent(x));
        }
    }

    //Heapifies down from pos x
    void heapifyD(int x)
    {
        unsigned int left = LC(x);
        unsigned int right = RC(x);

        int lpos = x;

        //determines if and which child to switch with
        if (left < MaxHeap.size() && MaxHeap[left] > MaxHeap[x]) 
        {
            lpos = left;
        }

        if (right < MaxHeap.size() && MaxHeap[right] > MaxHeap[lpos]) 
        {
            lpos = right;
        }
        
        //swaps and calls HeapifyD again
        if (lpos != x)
        {
            swap(MaxHeap[x], MaxHeap[lpos]);
            heapifyD(lpos);
        }
    }


public:

    //checks if maxheap is empty
    bool empty() 
    {
        if (MaxHeap.size() == 0)
            return true;
        else
            return false;
    }

    //inserts values then calls heapifyU
    void push(int x)
    {
        MaxHeap.push_back(x);
        int index = MaxHeap.size() - 1;
        heapifyU(index);
    }

    //Pops the next element
    int pop()
    {
        int temp = MaxHeap[0];
        MaxHeap[0] = MaxHeap.back();
        MaxHeap.pop_back();
        heapifyD(0);        
        return temp;
    }

    void topPicks(int test)
    {
        int count = 3;
        while (count > 0)
        {
            int value = pop();
            if (value == test)
            {
                cout << value << endl;
                count--;
            }
        }
    }
};
int main()
{
    
    int v1 = 0;
    PriorityQueue Test = PriorityQueue();
    for (int x = 0; x < 10000; x++)
    {
        v1 = rand() % 100;
        Test.push(v1);
    }
    Test.topPicks(23);

}