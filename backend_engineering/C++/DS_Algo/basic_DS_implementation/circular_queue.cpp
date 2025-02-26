#include <iostream>
#include <vector>

using namespace std;

class MyCircularQueue {
    vector<int> buffer;
    int capacity;
    int head_idx = -1;
    int tail_idx = -1;
    int size = 0;
public:
    MyCircularQueue(int k) {
        capacity = k;
        buffer.resize(capacity);
    }
    
    bool enQueue(int value) {
        if(size == capacity) return false;

        if(size == 0){
            buffer[0] = value;
            head_idx = 0;
            tail_idx = 0;
        }
        else{
            tail_idx = (tail_idx + 1) % capacity;
            buffer[tail_idx] = value;
        }
        
        ++size;
        return true;
    }
    
    bool deQueue() {
        if(size == 0) return false;
        
        head_idx = (head_idx + 1) % capacity;
        --size;
        return true;
    }
    
    int Front() {
        if(size == 0) return -1;
        else return buffer[head_idx];
    }
    
    int Rear() {
        if(size == 0) return -1;
        else return buffer[tail_idx];
    }
    
    bool isEmpty() {
        if(size == 0) return true;
        else return false;
    }
    
    bool isFull() {
        if(size == capacity) return true;
        else return false;
    }
};
