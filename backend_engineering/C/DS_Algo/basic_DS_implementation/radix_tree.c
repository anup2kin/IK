#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_CHILDREN 26

typedef struct RadixNode{
    bool isEnd;
    char *key;
    struct RadixNode *children[MAX_CHILDREN];
} RadixNode;

RadixNode* createRadixNode(const char *key){
    RadixNode *node = (RadixNode*)malloc(sizeof(RadixNode));
    node->key = strdup(key);
    node->isEnd = false;
    for(int i = 0; i < MAX_CHILDREN; i++){
        node->children[i] = NULL;
    }

    return node;
}

void freeRadixNode(RadixNode *node){
    if(node == NULL) return;

    for(int i = 0; i < MAX_CHILDREN; i++){
        if(node->children[i] != NULL){
            freeRadixNode(node->children[i]);
            node->children[i] = NULL;
        }
    }

    free(node->key);
    free(node);
}

typedef struct Radix{
    RadixNode *root;
} Radix;

Radix* createRadix(){
    Radix *radix = (Radix*)malloc(sizeof(Radix));
    radix->root = NULL;
    return radix;
}

void freeRadix(Radix *radix){
    freeRadixNode(radix->root);
    free(radix);
}

void insert(Radix *radix, const char *word){
    if(radix->root == NULL){
        radix->root = createRadixNode(word);
        radix->root->isEnd = true;
    }

    RadixNode *curNode = radix->root;

    while(true){
        int matachedIdx = 0;
        while(curNode->key[matachedIdx] == word[matachedIdx]) ++matachedIdx;

        if(matachedIdx == strlen(curNode->key)){
            if(word[matachedIdx] == '\0'){
                curNode->isEnd = true;
                return;
            }

            int index = word[matachedIdx] - 'a';
            if(curNode->children[index] == NULL){
                curNode->children[index] = createRadixNode(word + matachedIdx);
                curNode->children[index]->isEnd = true;
                return;
            }
            curNode = curNode->children[index];
            word = word + matachedIdx;
        }
        else{
            
        }
    }
    
}