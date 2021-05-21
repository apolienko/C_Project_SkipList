#include "SkipList.h"

int main(int argc, char *args[]) {
    if (argc != 3) {
        printf("IllegalArgumentException. InputFileName OutputFileName");
        exit(1);
    }
    skipList *sl =  input(args[1]);

    test(TRUE, contains(sl, 56), "test 1");
    test(TRUE, contains(sl, 44), "test 2");

    delete(sl, 56);
    delete(sl, 44);
    test(FALSE, contains(sl, 56), "test 3");
    test(FALSE, contains(sl, 44), "test 4");

    addNode(sl, 44);
    test(TRUE, contains(sl, 44), "test 5");

    filePrint(sl, args[2]);
    freeSkipList(sl);
    return 0;
}

void test(int expected, int actual, char* testName) {
    if(expected == actual){
        printf("\nPASSED %s", testName);
    }
    else {
        printf("\nFAILED %s ", testName);
    }
}
