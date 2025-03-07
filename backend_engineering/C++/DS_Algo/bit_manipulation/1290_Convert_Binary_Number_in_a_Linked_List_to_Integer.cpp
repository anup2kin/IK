#include <iostream>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


int getDecimalValue(ListNode* head) {
    int num = 0;
    // Using Horner's rule
    for(auto it = head; it != nullptr; it = it->next)
        num = (num << 1) + it->val;

    return num;
}