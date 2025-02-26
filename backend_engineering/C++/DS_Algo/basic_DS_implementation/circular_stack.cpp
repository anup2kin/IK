#include <iostream>
#include <vector>

using namespace std;

class Circular_stack{
private:
    vector<int> buffer;
    int capacity = 0;
    int top = -1;
    int size = 0;

public:
    Circular_stack(int k){
        capacity = k;
        buffer.resize(capacity);
    }

    bool is_full(){
        return capacity == size ? true : false;
    }

    bool is_empty(){
        return size == 0 ? true : false;
    }

    bool push(int value){
        if(size == capacity) return false;

        if(size == 0){
            top = 0;
            buffer[top] = value;
        }
        else{
            top = (top + 1) % capacity;
            buffer[top] = value;
        }

        ++size;
        return true;
    }

    int pop(){
        if(is_empty() == true) return -1;

        int value = buffer[top];
        top = (top - 1 + capacity) % capacity;
        --size;
        return value;
    }

    int peek(){
        if(is_empty() == true) return -1;

        return buffer[top];
    }

    void display() {
        if (is_empty()) {
            cout << "Stack is empty!" << endl;
            return;
        }
        cout << "Stack elements: ";
        for (int i = 0; i < size; i++) {
            cout << buffer[(top - i + capacity) % capacity] << " ";
        }
        cout << endl;
    }
};

int main() {
    Circular_stack stack(5); // Use the template

    try {
        stack.push(10);
        stack.push(20);
        stack.push(30);
        stack.push(40);
        stack.push(50);
        stack.display(); // Output: 50 40 30 20 10

        std::cout << "Popped: " << stack.pop() << std::endl; // Output: 50
        std::cout << "Popped: " << stack.pop() << std::endl; // Output: 40

        stack.push(60); // Overwrites the oldest element (circular behavior)
        stack.push(70);
        stack.display(); // Output: 70 60 30 20

        std::cout << "Peek: " << stack.peek() << std::endl; // Output: 70

        while(!stack.is_empty()){
            std::cout << "Popped: " << stack.pop() << std::endl;
        }

        stack.display();

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}