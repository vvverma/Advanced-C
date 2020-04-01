#include<stdio.h>
#include<stdlib.h>

typedef struct list {
    struct list* next;
    struct list* prev;
}linklist;

#define offsetof(type, member) ((size_t) &((type *)0)->member)

#define container_of(ptr, type, member) ({\
        const typeof( ((type *)0)->member ) *__mptr = (ptr);\
        (type *)( (char *)__mptr - offsetof(type,member) );})


#define list_node(list, node_type, member) ({\
        node_type *ptr;\
        ptr = container_of(list,node_type, member);})


#define list_node_next(node, member) ({\
        list_node((node->member.next),typeof(*node),member);})


#define for_each_node(list, node, member) \
        for(node = list_node(list,typeof(*node),member);\
        &node->member != NULL; node = list_node_next(node,member))


#define INIT_LIST_HEAD(list) ({NULL,NULL;})


void add_node_tail(linklist *list, linklist* newnode) {
    newnode->next = NULL;

    if(list->next == NULL) {
        newnode->prev = list;
        list->next = newnode;
    }
    else {
        linklist *mover;
        mover = list;
        while( mover && mover->next !=NULL) {
            mover = mover->next;
        }
        mover->next = newnode;
        newnode->prev = mover;
    }
}

typedef struct my_list {
    int data;
    linklist crosshead;
}testlistone;


void printlist(linklist* list) {
    linklist *mover;
    testlistone *nodes;
    for_each_node(list, nodes, crosshead) {
        printf("data is %d\n",nodes->data);
    }
}


int main(void) {

testlistone* t1 = (testlistone*) malloc(sizeof(testlistone));
t1->data = 1;
testlistone* t2 = (testlistone*) malloc(sizeof(testlistone));
t2->data = 2;
testlistone* t3 = (testlistone*) malloc(sizeof(testlistone));
t3->data = 3;

INIT_LIST_HEAD(&t1->crosshead);

add_node_tail(&t1->crosshead, &t2->crosshead);
add_node_tail(&t1->crosshead, &t3->crosshead);

printlist(&t1->crosshead);
printlist(&t1->crosshead);
free(t1);
free(t2);
free(t3);
return 0;
}