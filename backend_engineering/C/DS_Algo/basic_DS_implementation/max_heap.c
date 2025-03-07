#include <stdio.h>
#include <stdlib.h>

typedef struct MaxHeap{
    int *heap;
    int capacity;
    int last_item_idx;
} MaxHeap;

void swap(int *n1, int *n2){
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

void init_max_heap(MaxHeap *maxHeap, int size){
    maxHeap->heap = (int *)malloc(sizeof(int) * size);
    maxHeap->capacity = size;
    maxHeap->last_item_idx = -1;
}

void heapify_up(int *heap, int idx){
    while(idx > 0){
        int parent_idx = (idx - 1) / 2;
        if(heap[idx] > heap[parent_idx]){
            swap(&heap[idx], &heap[parent_idx]);
            idx = parent_idx;
        }
        else break;
    }
}

void push(MaxHeap *maxHeap, int val){
    if(maxHeap->last_item_idx == maxHeap->capacity - 1){
        int *temp = (int*)realloc(maxHeap->heap, sizeof(int) * maxHeap->capacity * 2);
        if(temp == NULL){
            printf("Memory allocation failed!\n");
            return;
        }

        maxHeap->capacity *= 2;
        maxHeap->heap = temp;
    }

    ++maxHeap->last_item_idx;
    maxHeap->heap[maxHeap->last_item_idx] = val;

    heapify_up(maxHeap->heap, maxHeap->last_item_idx);
}

void heapify_down(int *heap, int idx, int last_item_idx){
    while(1){
        int left_child_idx = 2 * idx + 1;
        int right_child_idx = 2 * idx + 2;
        int largest_idx = idx;

        if(left_child_idx <= last_item_idx && heap[left_child_idx] > heap[largest_idx]){
            largest_idx = left_child_idx;
        }

        if(right_child_idx <= last_item_idx && heap[right_child_idx] > heap[largest_idx]){
            largest_idx = right_child_idx;
        }

        if(idx != largest_idx){
            swap(&heap[idx], &heap[largest_idx]);
            idx = largest_idx;
        }
        else break;
    }
}

int pop(MaxHeap *maxHeap, int *isEmpty){
    *isEmpty = 0;

    if(maxHeap->last_item_idx == -1){
        *isEmpty = 1;
        return -1;
    }

    int poppedValue = maxHeap->heap[0];
    swap(&maxHeap->heap[0], &maxHeap->heap[maxHeap->last_item_idx]);
    --maxHeap->last_item_idx;

    heapify_down(maxHeap->heap, 0, maxHeap->last_item_idx);

    return poppedValue;
}

void heap_sort_in_place(int *heap, int size){
    for(int i = size / 2 - 1; i >= 0; i--){
        heapify_down(heap, i, size - 1);
    }

    for(int i = size - 1; i >= 0; i--){
        swap(&heap[0], &heap[i]);
        heapify_down(heap, 0, i - 1);
    }
}

void free_max_heap(MaxHeap *maxHeap){
    free(maxHeap->heap);
    maxHeap->heap = NULL;
}

int main() {
    MaxHeap maxHeap;
    init_max_heap(&maxHeap, 5); // Initial capacity of 5

    push(&maxHeap, 10);
    push(&maxHeap, 5);
    push(&maxHeap, 20);
    push(&maxHeap, 2);
    push(&maxHeap, 15);
    push(&maxHeap, 30); // Capacity will be doubled here.

    int isEmpty;
    int poppedValue;

    while (1) {
        poppedValue = pop(&maxHeap, &isEmpty);
        if (isEmpty) {
            break;
        }
        printf("%d ", poppedValue);
    }
    printf("\n");

    free_max_heap(&maxHeap);

    int heap[6] = {10, 5, 20, 2, 15, 30};
    heap_sort_in_place(heap, sizeof(heap) / sizeof(int));
    for(int i = 0; i < sizeof(heap) / sizeof(int); i++){
        printf("%d, ", heap[i]);
    }
    
    return 0;
}