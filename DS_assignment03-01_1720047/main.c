//
//  main.c
//  Data Structure
//  Assignment3-1
//  작성자 : 국어국문학과 1720047 이윤경
//
//
#include <stdio.h>
#include <stdlib.h>


typedef int element;
typedef struct DlistNode {
    element data;
    struct DlistNode *llink;
    struct DlistNode *rlink;
} DlistNode;

//head node
void init(DlistNode *phead) {
    phead -> llink = phead;
    phead -> rlink = phead;
}
void display(DlistNode *phead) {
    DlistNode *p;
    printf("headnode = %x\n", phead);
    for (p=phead->rlink; p!=phead ; p=p->rlink) {
        printf("<---| %x | %d | %x | --->\n", p->llink, p->data, p->rlink);
    }
    printf("\n");
}
//insert 'new_node' into the right of 'before'
//new_node를 before의 오른쪽에 삽입하는 방식
//리스트의 맨 처음과 끝에 new_node를 넣어줌
void dinsert_node(DlistNode *before, DlistNode *new_node) {
    new_node->llink = before;
    new_node->rlink = before->rlink;
    before->rlink->llink = new_node;
    before->rlink = new_node;
}

int main(void) {
    
    DlistNode head_node;
    DlistNode *p[10];
    
    init(&head_node); //자기 자신을 참조하도록 initialization
    for (int i=0 ; i<2 ; i++) {
        p[i] = (DlistNode *)malloc(sizeof(DlistNode));
        p[i] -> data = i;
        dinsert_node(&head_node, p[i]);
    }
    
    DlistNode *new_node;
    new_node = (DlistNode *)malloc(sizeof(DlistNode));
    new_node->data = 100;
    
    //list의 맨 앞에 집어넣는 경우
    //display 출력문에서 new_node가 가진 값 100이 출력되고, new_node의 llink는 headnode를 가리킴, rlink는 맨 앞에 위치했던 값 1을 가리킴
    //new_node를 이중 연결 리스트의 맨 앞에 넣는 경우 해당 함수를 그대로 사용할 수 있음
    dinsert_node(&head_node, new_node);
    
    DlistNode *new_node2;
    new_node2 = (DlistNode *)malloc(sizeof(DlistNode));
    new_node2->data = 200;
    
    //list의 맨 뒤에 집어넣는 경우
    //parameter로 집어넣게 되는 값에 대해 앞의 경우와 차이가 있음. 리스트의 맨 뒤에 넣어야 하기 때문에 headnode의 llink를 사용해 리스트 맨 뒤로 접근한다. dinsert_node는 포인터를 파라미터로 받게 설정되어있으므로 head_node.llink의 주소값을 해당 함수의 인자로 대입한다.
    //display 출력문에서 new_node2 가진 값 200이 출력되고, new_node2의 rlink는 headnode를 가리킴, link는 맨 뒤에 위치했던 값 1을 가리킴
    //new_node를 이중 연결 리스트의 맨 뒤에 넣는 경우 해당 함수를 그대로 사용할 수 있음
    dinsert_node(head_node.llink, new_node2);
    
    
    
    display(&head_node);
    printf("%x\n", &(head_node.llink));
    
    
    return 0;
}
