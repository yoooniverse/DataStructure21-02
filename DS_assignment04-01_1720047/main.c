//
//  main.c
//  DS_assignment04_1720047
//  Assignment4-1
//  작성자 : 국어국문학과 1720047 이윤경
//

#include <stdio.h>


// linked_stack.cpp : Defines the entry point for the console application.
//Re-implement the functions in the code using circular doubly linked list which is defined as below, and then run the main function of the code.
//#include <stdafx.h>  오류로 인한 주석처리
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

//스택에 들어갈 데이터는 정수형으로 설정
typedef int element;


//circular doubly linked list
//문제에서 주어진 구조체
typedef struct DlistNode {
    element data;
    struct DlistNode *llink;
    struct DlistNode *rlink;
} DlistNode;


typedef struct {
    DlistNode *head_p;
} DLinkedListType;

//스택 초기화.
void init(DLinkedListType *s) {
    s->head_p = NULL;
}
//
int is_empty(DLinkedListType *s) {
    return (s->head_p == NULL);
}

void push(DLinkedListType *s, element data) {
    DlistNode *temp = (DlistNode *)malloc(sizeof(DlistNode));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return;
    } 
    else {
        temp->data = data;
        temp->llink = s->head_p;
        temp->rlink = s->head_p;
        s->head_p = temp;
    }
}

element pop(DLinkedListType *s)
{
    if (is_empty(s)) {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }
    else {
        DlistNode *temp = s->head_p;
        int item = temp->data;
        s->head_p = s->head_p->rlink;
        free(temp);
        return item;
    }
}


element peek(DLinkedListType *s) {
    
    if (is_empty(s)) {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }
    else {
        return s->head_p->data;
    }
}

int main(void) {

    DLinkedListType s; //헤드포인터 만듬 타입구조체 선언했으므로.
    
    init(&s);
    
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);
    push(&s, 4);
    push(&s, 5 );


    printf("4: %d\n", pop(&s));
    printf("5: %d\n", pop(&s));
    printf("6: %d\n", pop(&s));
    
    return 0;
}




