#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 100

typedef struct Node{
    int key;
    int val;
    struct Node *next;
} Node;

typedef struct{
    Node *table[TABLE_SIZE];
}HashTable;

void init_hash_table(HashTable *hashTable){
    for(int i = 0; i < TABLE_SIZE; i++){
        hashTable->table[i] = NULL;
    }
}

void put(HashTable *hashTable, int key, int val){
    int idx = key % TABLE_SIZE;

    Node *head = hashTable->table[idx];
    Node *cur_node = head;
    while(cur_node != NULL){
        if(cur_node->key == key){
            cur_node->val = val;
            return;
        }

        cur_node = cur_node->next;
    }

    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->key = key;
    new_node->val = val;
    new_node->next = head;

    hashTable->table[idx] = new_node;
}

int get(HashTable *hashTable, int key, int *found){
    int idx = key % TABLE_SIZE;
    *found = 1;

    Node *cur_node = hashTable->table[idx];
    while(cur_node != NULL){
        if(cur_node->key == key) return cur_node->val;
        cur_node = cur_node->next;
    }

    *found = 0;
    return -1;
}

void remove(HashTable *hashTable, int key){
    int idx = key % TABLE_SIZE;

    Node *cur_node = hashTable->table[idx];
    Node *prev_node = NULL;
    while(cur_node != NULL){
        if(cur_node->key == key){
            if(prev_node != NULL){
                prev_node->next = cur_node->next;
            }
            else{
                hashTable->table[idx] = cur_node->next;
            }
            
            free(cur_node);
            return;
        }
        else{
            prev_node = cur_node;
            cur_node = cur_node->next;
        }
    }
}

void print_hash_table(HashTable *hashTable) {
    printf("\nHash Table Contents:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        Node *cur_node = hashTable->table[i];
        while (cur_node != NULL) {
            printf("(%d : %d) -> ", cur_node->key, cur_node->val);
            cur_node = cur_node->next;
        }
        printf("NULL\n");
    }
}

void free_hash_table(HashTable *hashTable){
    for(int i = 0; i < TABLE_SIZE; i++){
        Node *cur_node = hashTable->table[i];
        while(cur_node != NULL){
            Node *temp = cur_node;
            cur_node = cur_node->next;
            free(temp);
        }
        hashTable->table[i] = NULL;
    }
}

int main() {
    HashTable ht;
    init_hash_table(&ht);

    // Insert key-value pairs
    put(&ht, 1, 100);
    put(&ht, 2, 200);
    put(&ht, 3, 300);

    // Retrieve values
    int found;
    int val1 = get(&ht, 1, &found);
    printf("1 -> %s%d\n", found ? "" : "Not Found: ", found ? val1 : -1);

    int val2 = get(&ht, 2, &found);
    printf("2 -> %s%d\n", found ? "" : "Not Found: ", found ? val2 : -1);

    int val3 = get(&ht, 3, &found);
    printf("3 -> %s%d\n", found ? "" : "Not Found: ", found ? val3 : -1);

    // Remove a key
    remove(&ht, 2);
    printf("\nAfter removing '2':\n");
    print_hash_table(&ht);

    // Free allocated memory
    free_hash_table(&ht);
    return 0;
}