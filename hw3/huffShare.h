#ifndef HUFFSHAREH
#define HUFFSHAREH


void initCodeArr();
struct node ** create_node_list();
int comparator(const void *p, const void *q);
struct node * form_tree(struct node ** list);
struct node * take_two_lowest(struct node **list);
void freeEverything(struct node* list);

#endif