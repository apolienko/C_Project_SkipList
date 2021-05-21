//
// Created by 1 on 03.05.2021.
//

#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_LEVEL 5
#define TRUE 1
#define FALSE 0

typedef struct Node {
    int key;
    struct Node *next[];
} node;

typedef struct SkipList {
    int level;
    struct Node *head;
} skipList;

void addNode(skipList *sl, int key);
void delete(skipList *sl, int key);
skipList* input(char *inputFile);
void filePrint(skipList *sl, char *outputFile);
void freeSkipList(skipList *sl);
int contains(skipList *sl, int key);
void test(int expected, int actual, char* testName);

#endif SKIPLIST_H