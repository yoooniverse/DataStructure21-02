//
//  main.c
//  Data Structure
//  Assignment3-2
//  작성자 : 국어국문학과 1720047 이윤경
//
//
#include <stdio.h>
#include <stdlib.h>

//구조체 설정 : 단일 연결 리스트이므로 link는 하나만 만든다.
typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

ListNode* insert(ListNode* head, element value) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->data = value;
    node->link = NULL;
    
    if (head == NULL) {
        head = node;
        return head;
    }
    else {
        ListNode* p;
        for (p=head ; p->link != NULL ; p = p->link);
        p->link = node;
        return head;
    }
}

ListNode* merge(ListNode* list1, ListNode* list2){
    ListNode* list3 = NULL;
    ListNode* p1, * p2, * p3 = NULL;
    if (list1 == NULL) return list2;
    else if (list2 == NULL) return list1;
    else {
        p1 = list1;
        p2 = list2;
        while((p1 != NULL) || (p2 != NULL)) {
            if (p1 != NULL && p2 != NULL) {
                if (p1->data < p2->data) {
                    list3 = insert(list3, p1->data);
                    p1 = p1->link;
                }
                else {
                    list3 = insert(list3, p2->data);
                    p2 = p2->link;
                }
            }
            else if (p1 != NULL) {
                list3 = insert(list3, p1->data);
                p1 = p1->link;
            }
            else if (p2 != NULL) {
                list3 = insert(list3, p2->data);
                p2 = p2->link;
            }
        }
        return list3;
    }
}

int main(void) {
    int arr1[] = {1, 2, 5, 10, 15, 20, 25};
    int arr2[] = {3, 7, 8, 15, 18, 30};
    
    ListNode* head1 = NULL;
    ListNode* head2 = NULL;
    for (int i=0 ; i<sizeof(arr1) / sizeof(int); i++) {
        head1 = insert(head1, arr1[i]);
    }
    
    for (int i=0 ; i<sizeof(arr2) / sizeof(int); i++) {
        head2 = insert(head2, arr2[i]);
    }
    
    ListNode* list = merge(head1, head2);
    for (ListNode* p = list ; p != NULL ; p = p->link) {
        printf("%d, ", p->data);
    }
    printf("\n" );
    return 0;
}
