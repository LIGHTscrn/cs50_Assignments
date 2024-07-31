#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
    char *phrase;
    struct node *next;
}
node;
int main(void)
{
    //struct node in place so we can start linked list
    node *list = NULL;
    node *n = malloc(sizeof(node));
    n->phrase = "HI";
    n->next = NULL;
    list = n;
    n = malloc(sizeof(node));
    n->phrase = "Hey";
    n->next = list;
    list = n;
    free(n);
    node *ptr = list->next;
    while(ptr != NULL)
    {
        ptr = list->next;
        free(list);
        list = ptr;
    }
return 0;
}


