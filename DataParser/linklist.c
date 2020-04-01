#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"linklist.h"

void add_list(Node** head, char* new_string) {
    Node* new_node = (Node*)malloc(sizeof(Node));

    new_node->string  = (char*) malloc(strlen(new_string)+1);
    strcpy(new_node->string, new_string);
    new_node->next = NULL;

    if (*head == NULL) {
        (*head) = new_node;
    }
    else {
        Node* move;
        move = *head;
        while(move->next != NULL) {
            move = move->next;
        }
        //Adding a node at tail
        move->next = new_node;
    }
}


void print_list(struct Node *node) {
    printf("[ ");
    while (node && (node->next != NULL)) {
        printf("%s,\n",node->string);
        node = node->next;
    }

    if(node)
        printf("%s",node->string);
    printf(" ]\n");
}


void delete_list(struct Node *node) {
    Node* temp;
    while (node != NULL) {
        temp = node->next;
        free(node);
        node = temp;
    }

}

int length_list(struct Node *node) {
    int count;
    count = 0;
    while (node != NULL) {
        node = node->next;
        count++;
    }
    return count;
}
