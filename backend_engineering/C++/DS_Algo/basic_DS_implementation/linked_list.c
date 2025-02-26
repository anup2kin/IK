#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int key;
    int val;
    struct Node *next;
    struct Node *prev;
} Node;

static const int HASH_TABLE_SIZE = 100;

void add_node(Node **head, Node **tail, int key, int val){
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->key = key;
    new_node->val = val;
    new_node->prev = NULL;
    new_node->next = NULL;

    if(*head == NULL){
        *head = new_node;
        *tail = new_node;
        return;
    }

    (*tail)->next = new_node;
    new_node->prev = *tail;
    *tail = new_node;
}

void delete_node(Node **head, Node **tail, int key){
    if(*head == NULL) return;

    Node *dummy = (Node*)malloc(sizeof(Node));
    dummy->key = INT_MIN;
    dummy->next = *head;
    (*head)->prev = dummy;

    Node *cur_node = *head;
    Node *prev_node = dummy;
    while(cur_node != NULL){
        if(cur_node->key == key){
            prev_node->next = cur_node->next;
            if(cur_node->next != NULL){
                cur_node->next->prev = prev_node;
            }

            if(cur_node == *tail){
                *tail = prev_node;
                if(prev_node == dummy){
                    *tail = NULL;
                }
            }

            *head = dummy->next;
            if(*head != NULL){
                (*head)->prev = NULL;
            }
            else{
                *tail = NULL;
            }

            free(cur_node);
            free(dummy);
            return;
        }

        prev_node = cur_node;
        cur_node = cur_node->next;
    }
}


void print_linked_list(Node *head, Node *tail){
    printf("\nPrinting linked list\n");
    for(Node *cur_node = head; cur_node != NULL; cur_node = cur_node->next){
        printf("%d: %d, ", cur_node->key, cur_node->val);
    }
}


int main() {
    Node *head = NULL;
    Node *tail = NULL;

    add_node(&head, &tail, 1, 10);
    add_node(&head, &tail, 2, 20);
    add_node(&head, &tail, 3, 30);

    // ... (Print or use the list) ...
    print_linked_list(head, tail);

    delete_node(&head, &tail, 2); // Delete the node with key 2

    // ... (Print or use the list again) ...

    delete_node(&head, &tail, 1); // Delete the head
    delete_node(&head, &tail, 3); // Delete the tail

    // ... (Print or use the list again) ...  Should be empty now.
    print_linked_list(head, tail);
    
    return 0;
}