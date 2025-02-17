#include <iostream>
#include <vector>

using namespace std;

class Max_heap {
public:
    Max_heap(int size = 1) {
        heap.reserve(size); // Use reserve instead of resize to prevent unused elements
        idx_last_item = -1;
    }

    void push(int num) {
        // Increase heap size dynamically
        heap.push_back(num);
        // Move idx_last_item to point to first empty slot in the heap vector
        ++idx_last_item;

        // Heapify up
        heapify_up(idx_last_item);
    }

    int pop() {
        if (idx_last_item < 0) {
            throw runtime_error("Heap is empty");
        }

        int popped_value = heap[0];

        // Swap root with the last element
        heap[0] = heap[idx_last_item];
        heap.pop_back(); // Remove the last element
        --idx_last_item;

        // Heapify down
        heapify_down();
        return popped_value;
    }

    void heap_sort(vector<int> &arr)
    {
        int idx_last_item = arr.size() - 1;
        int idx_valid_from = arr.size() / 2 - 1;

        for(int i = idx_valid_from; i >= 0; i++)
            heapify_down(arr, i, idx_last_item);

        // Now write code for pop
        for(int i = 0; i < arr.size(); i++)
            pop(arr, idx_last_item);
    }

private:
    void heapify_up(int idx_child){
        while (idx_child > 0) {
            int idx_parent = (idx_child - 1) / 2;
            
            if (heap[idx_child] > heap[idx_parent]) {
                swap(heap[idx_child], heap[idx_parent]);
                idx_child = idx_parent;
            } else {
                break;
            }
        }
    }

    void heapify_down(vector<int> &heap, int idx_parent, int &idx_last_item){
        while (true) {
            int idx_left_child = idx_parent * 2 + 1;
            int idx_right_child = idx_parent * 2 + 2;
            int idx_largest = idx_parent;

            if (idx_left_child <= idx_last_item && heap[idx_left_child] > heap[idx_largest]) {
                idx_largest = idx_left_child;
            }

            if (idx_right_child <= idx_last_item && heap[idx_right_child] > heap[idx_largest]) {
                idx_largest = idx_right_child;
            }

            if (idx_largest != idx_parent) {
                swap(heap[idx_parent], heap[idx_largest]);
                idx_parent = idx_largest;
            } else {
                break;
            }
        }
    }

    void heapify_down(){
        return heapify_down(heap, 0, idx_last_item);
    }

    int pop(vector<int> &arr, int idx_last_item){
        if (idx_last_item < 0) {
            throw runtime_error("Heap is empty");
        }

        int popped_value = arr[0];

        // Swap root with the last element
        arr[0] = arr[idx_last_item];
        --idx_last_item;

        // Heapify down
        heapify_down(arr, 0, idx_last_item);
        return popped_value;
    }
private:
    vector<int> heap;
    int idx_last_item;
};

int main() {
    /*Max_heap heap(10);

    heap.push(15);
    heap.push(10);
    heap.push(30);
    heap.push(40);
    heap.push(50);

    for(int i = 0; i < 5; i++)
    cout << "Popped element: " << heap.pop() << endl;
    */

   vector<int> arr{1, 2, 3, 4, 5, 6, 7, 8, 9};
   Max_heap max_heap;

    max_heap.heap_sort(arr);

    for(const auto &num : arr) std::cout << num << endl;
    
    return 0;
}
