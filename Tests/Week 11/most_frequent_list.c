#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int data;
};

int most_frequent(struct node *head);

struct node *strings_to_list(int len, char *strings[]);

// DO NOT CHANGE THIS MAIN FUNCTION

int main(int argc, char *argv[]) {
    // create linked list from command line arguments
    struct node *head = strings_to_list(argc - 1, argv + 1);

    int result = most_frequent(head);
    printf("%d\n", result);

    return 0;
}

// return the value which occurs most frequently in a linked list
// if several values are equally most frequent
// the value that occurs earliest in the list is returned
int most_frequent(struct node *head) {

    int highestInt;
    int highestCount = 0;

    struct node *current = head;
    while (current != NULL) {

        struct node *cursor = head;

        int cursorCount = 0;

        while (cursor != NULL) {
            if (current->data == cursor->data) {
                cursorCount++;
            }
            cursor = cursor->next;
        }
        if (cursorCount > highestCount) {
            highestInt = current->data;
            highestCount = cursorCount;
        }

        current = current->next;
    }
    // PUT YOUR CODE HERE (change the next line!)
    return highestInt;

}


// DO NOT CHANGE THIS FUNCTION

// create linked list from array of strings
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    for (int i = len - 1; i >= 0; i = i - 1) {
        struct node *n = malloc(sizeof(struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
    }
    return head;
}
