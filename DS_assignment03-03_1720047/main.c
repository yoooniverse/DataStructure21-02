//
//  main.c
//  Data Structure
//  Assignment3-3
//  작성자 : 국어국문학과 1720047 이윤경
//

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

typedef struct {
    ListNode *head; //head pointer to the first node
    ListNode *tail; //tail pointer
    int length; //# of nides
} ListType;
ListType list1;

void init(ListType *list) {
    if (list == NULL) return;

    list->length = 0;
    list->head = NULL;
}

int is_empty(ListType *list){
    if (list->head == NULL) return 1;
    else return 0;
}

int get_length(ListType *list) {
    return list->length;
}

//return node pointer of 'pos' in the list.
//get_node_at : converts a position to node pointer
ListNode* get_node_at(ListType *list, int pos) {
    int i;
    ListNode *tmp_node = list->head;
    if (pos < 0) return NULL;
    for (i=0 ; i<pos ; i++)
        tmp_node = tmp_node->link;
    return tmp_node;
}

void insert_node(ListNode** phead, ListNode* p, ListNode* new_node){
    if (*phead == NULL) {
        *phead = new_node;
        (*phead)->link = NULL;
    } else if (p == NULL){
        new_node->link = *phead;
        *phead = new_node;
    } else {
        new_node->link = p->link;
        p->link = new_node;
    }
}

void remove_node(ListNode** phead, ListNode* p, ListNode* removed){
    if (*phead == NULL) return;
    if (p == NULL) {
        *phead = (ListNode*)(*phead)->link;
    }
    else {
        p->link = removed->link;
    }
    free(removed); //null이어도 에러가 나지 않음
}



//insert new data at the 'position'
void add(ListType *list, int position, element data) {
    ListNode *p;
    
    if((position >= 0) && (position <= list->length)) {
        ListNode *node = (ListNode*)malloc(sizeof(ListNode));
        
        if (node == NULL) perror("Memory allocation error");
        
        node->data = data;
        p = get_node_at(list, position-1);
        insert_node(&(list->head), p, node);
        list->length++;
    }
}

void add_first(ListType *list, element data) {
    add(list, 0, data);
}

void add_last(ListType *list, element data) {
    add(list, get_length(list), data);
}

void delete(ListType *list, int pos) {
    
    if (!is_empty(list) && (pos >=0) && (pos < list->length)) {
        ListNode *p = get_node_at(list, pos-1);
        ListNode *removed = get_node_at(list, pos);
        remove_node(&(list->head), p, removed);
        list->length--;
    }
}

void delete_first(ListType *list) {
    delete(list, 0);
}

void delete_last(ListType *list) {
    delete(list, get_length(list) - 1);
}


element get_entry (ListType *list, int pos) {
    ListNode *p;
    if (pos >= list -> length) perror("position error");
    p = get_node_at(list, pos);
    return p->data;
}

void display(ListType *list) {
    int i;
    ListNode *node = list->head;
    printf("(");
    for (i=0 ; i<list->length; i++) {
        printf(" %d ", node->data);
        node = node->link;
    }
    printf(")\n");
}

int is_in_list(ListType *list, element item) {
    ListNode *p;
    p = list->head;
    while ((p!=NULL)) {
        if (p->data == item) break;
        p = p->link;
    }
    if (p==NULL) return FALSE;
    else return TRUE;
}


int main(void) {
    ListType list1;
    init(&list1);
    add_first(&list1, 20);
    add_last(&list1, 30);
    add_first(&list1, 10);
    add_last(&list1, 40);
    add(&list1, 2, 70);
    display(&list1);
    
    delete(&list1, 2);
    delete_first(&list1);
    delete_last(&list1);
    display(&list1);
    
    printf("%s\n", is_in_list(&list1, 20) == TRUE ? "TRUE" : "FALSE");
    printf("%d\n", get_entry(&list1, 0));
    
    return 0;
}
