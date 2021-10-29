//
//  main.c
//  DS_assignment05-02_1720047
//  Assignment5-2
//  작성자 : 국어국문학과 1720047 이윤경
//  
//

//Implement the function that finds a predecessor of node in the inorder traversal.

//            G7
//       C3       F6
//    A1   B2   D4   E5

#include <stdio.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right, *parent;
} TreeNode;


TreeNode n1 = { 'A', NULL, NULL, NULL };
TreeNode n2 = { 'B', NULL, NULL, NULL };
TreeNode n3 = { 'C', &n1, &n2, NULL };
TreeNode n4 = { 'D', NULL, NULL, NULL };
TreeNode n5 = { 'E', NULL, NULL, NULL };
TreeNode n6 = { 'F', &n4, &n5, NULL };
TreeNode n7 = { 'G', &n3, &n6, NULL };
TreeNode *exp_root = &n7;

//주어진 노드의 이전 노드 찾기.
TreeNode *tree_predecessor(TreeNode *p) {
    if (p->left != NULL) {
        p = p->left;   //p를 왼쪽 서브트리로 지정한다음
        while (p->right) p = p->right;    //가장 오른쪽에 있는 노드까지 가도록 while 반복 사용
        return p;   //가장 오른쪽으로 가면 해당 노드를 반납한다. 그게 이전 노드의 predecessor가 됨.
    }
    
    TreeNode *y = p->parent;
    while (y != NULL && p == y->left) {
        p = y;
        y = y->parent;
    }
    return y;
}


int main(void) {
    TreeNode *q = exp_root;
    n1.parent = &n3;
    n2.parent = &n3;
    n3.parent = &n7;
    n4.parent = &n6;
    n5.parent = &n6;
    n6.parent = &n7;
    n7.parent = NULL;
    
    //go to the rightmost node
    while (q->right) q = q->right;
    
    do {
        printf("%c\n", q->data);
        q = tree_predecessor(q);
    } while(q);
    
    return 0;
}
