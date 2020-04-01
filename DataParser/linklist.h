
typedef struct Node {
    char* string;
    struct Node *next;
}Node;

void add_list(Node** head, char* new_string);
void print_list(struct Node *node);
int length_list(struct Node *node);
void delete_list(struct Node *node);