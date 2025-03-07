#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CHILDREN 26

typedef struct TrieNode{
    bool isWord;
    struct TrieNode* children[MAX_CHILDREN];
} TrieNode;

TrieNode* createTrieNode(){
    TrieNode *root = (TrieNode*)malloc(sizeof(TrieNode));

    root->isWord = false;
    for(int i = 0; i < MAX_CHILDREN; i++){
        root->children[i] = NULL;
    }

    return root;
}

typedef struct Trie{
    TrieNode *root;
} Trie;

Trie* createTrie(){
    Trie *trie = (Trie *)malloc(sizeof(Trie));
    trie->root = createTrieNode();
    return trie;
}

void insert(Trie *trie, const char *word){
    TrieNode *curNode = trie->root;
    for(int i = 0; i < strlen(word); i++){
        int idx = word[i] - 'a';
        TrieNode *child = curNode->children[idx];
        if(child == NULL){
            curNode->children[idx] = createTrieNode();
            child = curNode->children[idx];
        }
        curNode = child;
    }

    curNode->isWord = true;
}

bool search(Trie *trie, const char *word){
    TrieNode *curNode = trie->root;
    for(int i = 0; i < strlen(word); i++){
        int idx = word[i] - 'a';
        if(curNode->children[idx] == NULL) return false;
        curNode = curNode->children[idx];
    }

    return curNode->isWord;
}

bool startsWith(Trie *trie, const char *prefix){
    TrieNode *curNode = trie->root;
    for(int i = 0; i < strlen(prefix); i++){
        int idx = prefix[i] - 'a';
        if(curNode->children[idx] == NULL) return false;
        curNode = curNode->children[idx];
    }
    return true;
}

void freeTrieNode(TrieNode *root){
    for(int i = 0; i < MAX_CHILDREN; i++){
        if(root->children[i] != NULL){
            freeTrieNode(root->children[i]);
            root->children[i] = NULL;
        }
    }
    free(root);
}

void freeTrie(Trie *trie){
    freeTrieNode(trie->root);
    trie->root = NULL;
    free(trie);
}

int main() {
    Trie* trie = createTrie();

    insert(trie, "apple");
    insert(trie, "app");

    printf("Search apple: %s\n", search(trie, "apple") ? "Found" : "Not Found");
    printf("Search app: %s\n", search(trie, "app") ? "Found" : "Not Found");
    printf("Search banana: %s\n", search(trie, "banana") ? "Found" : "Not Found");
    printf("Prefix 'ap': %s\n", startsWith(trie, "ap") ? "Exists" : "Doesn't Exist");
    printf("Prefix 'ba': %s\n", startsWith(trie, "ba") ? "Exists" : "Doesn't Exist");

    freeTrie(trie);
    return 0;
}
