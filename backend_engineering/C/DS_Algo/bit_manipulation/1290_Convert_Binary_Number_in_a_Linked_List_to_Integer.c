#include <stdio.h>

// Definition for singly-linked list.
typedef struct ListNode {
    int val;
    ListNode *next;
} ListNode;


int getDecimalValue(ListNode* head) {
    int num = 0;
    // Using Horner's rule
    for(ListNode* it = head; it != NULL; it = it->next)
        num = (num << 1) + it->val;

    return num;
}