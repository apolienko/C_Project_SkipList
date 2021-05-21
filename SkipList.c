//
// Created by 1 on 03.05.2021.
//

#include "SkipList.h"

static node *buildNode(int level, int key) {

    int i;
    node *nd = (node *)malloc(sizeof(node) + level * sizeof(node));
    nd->key = key;

    for (i = 0; i < level; i++) {
        nd->next[i] = NULL;
    }

    return nd;
}

static skipList *buildSkipList(void) {

    skipList *sl = (skipList *)malloc(sizeof(skipList));
    sl->head = buildNode(MAX_LEVEL, 0);
    sl->level = 1;
    srand(time(NULL));
    return sl;
}

static int getLevel() {

    int coin = 1;
    int level = 0;

    while (coin == 1 && level < MAX_LEVEL) {
        level++;
        coin = (rand() % 2);
    }

    return level;
}

void addNode(skipList *sl, int key) {
    node *update[MAX_LEVEL];
    node *nd = sl->head;

    int i;
    int level;

    level = getLevel();
    if (level > sl->level) {
        for (i = sl->level; i < level; i++) {
            update[i] = sl->head;
        }
        sl->level = level;
    }

    for (i = sl->level - 1; i >= 0; i--) {
        while (nd->next[i] != NULL && nd->next[i]->key < key) {
            nd = nd->next[i];
        }
        update[i] = nd;
    }

    node *newNode = buildNode(level, key);
    for (i = 0; i < level; i++) {
        newNode->next[i] = update[i]->next[i];
        update[i]->next[i] = newNode;
    }

}

static void deleteNode(skipList *sl, node *nd, node **update) {

    int i;

    for (i = 0; i < sl->level; i++) {
        if (update[i]->next[i] == nd) {
            update[i]->next[i] = nd->next[i];
        }
    }

    for (i = i - 1; i >= 0; i--) {
        if (sl->head->next[i] == NULL) {
            sl->level--;
        }
    }
}

void delete(skipList *sl, int key) {

    node *update[MAX_LEVEL];
    node *nd;
    int i;

    nd = sl->head;
    for (i = sl->level - 1; i >= 0; i--) {
        while (nd->next[i] && nd->next[i]->key < key) {
            nd = nd->next[i];
        }
        update[i] = nd;
    }

    nd = nd->next[0];

    if (nd != NULL && nd->key == key) {
        deleteNode(sl, nd, update);
        free(nd);
    }
}

void filePrint(skipList *sl, char *outputFile) {
    node *nd;
    int i;

    FILE *fp;
    if ((fp = fopen(outputFile, "w")) == NULL) {
        printf("Fail to open or create %s\n",outputFile);
        exit(1);
    }

    for (i = 0; i < MAX_LEVEL; i++) {
        nd = sl->head->next[i];
        fprintf(fp, "Level %d : ", i);

        while (nd != NULL) {
            fprintf(fp, "%d -> ", nd->key);
            nd = nd->next[i];
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

skipList* input(char *inputFile) {
    skipList *sl = buildSkipList();

    FILE *fp;

    if ((fp = fopen(inputFile, "r")) == NULL) {
        printf("Failed to open %s\n",inputFile);
        exit(1);
    }

    int temp;

    for(int i = 0; i < 20; i++) {
        fscanf(fp, "%d", &temp);
        addNode(sl, temp);
    }

    fclose(fp);

    return sl;
}

void freeSkipList(skipList *sl) {

    node *nd, *next;

    nd = sl->head->next[0];
    free(sl->head);

    while (nd) {
        next = nd->next[0];
        free(nd);
        nd = next;
    }

    free(sl);

}

int contains(skipList *sl, int key) {

    node *nd = sl->head;

    while (nd->next[0] != NULL && nd->key != key) {
        nd = nd->next[0];
    }

    if (nd->key == key) {
        return TRUE;
    } else {
        return FALSE;
    }

}
