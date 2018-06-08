#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct node {
    struct node *next;
    int data;
};

int count_farnarkles(struct node *head1, struct node *head2);

struct node *strings_to_list(int len, char *strings[]);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(int argc, char *argv[]) {
    // create two linked lists from command line arguments
    int dash_arg = argc - 1;
    while (dash_arg > 0 && strcmp(argv[dash_arg], "-") != 0) {
        dash_arg = dash_arg - 1;
    }
    struct node *head1 = strings_to_list(dash_arg - 1, &argv[1]);
    struct node *head2 = strings_to_list(argc - dash_arg - 1, &argv[dash_arg + 1]);

    int result = count_farnarkles(head1, head2);
    printf("%d\n", result);

    return 0;
}

// Return the number of farnarkles in the two lists, i.e. the number of
// values which occur at the same position in both linked lists.
int count_farnarkles(struct node *head1, struct node *head2) {

    /* A tile is counted as an Farnarkle if it has the same number
            as the tile in the same position in the hidden sequence. */

    int farnarkles = 0;

    struct node *curr1 = head1;
    struct node *curr2 = head2;

    while (curr1 != NULL && curr2 != NULL) {
        if (curr1->data == curr2->data) {
            farnarkles++;
        }
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    return farnarkles;
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
