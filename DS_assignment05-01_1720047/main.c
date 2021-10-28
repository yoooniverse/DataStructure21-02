//
//  main.c
//  DS_assignment05_1720047
//  Assignment5-1
//  작성자 : 국어국문학과 1720047 이윤경
//
//

// Implement the function that finds a successor of node in the inorder traversal

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



TreeNode *tree_successor(TreeNode *p) {
    //p의 right subtree가 not null이다. 그 말은 inorder에 의해 가장 왼쪽부터 가서 inorder 순서대로 훑어야 한다는 의미. go to the leftmost node of right subtree!
    if (p->right != NULL) {
        p = p->right;   //p를 오른쪽 서브트리로 지정한다음
        while (p->left) p = p->left;    //가장 왼쪽에 있는 노드까지 가도록 while 반복 사용
        return p;   //가장 왼쪽으로 가면 해당 노드를 반납한다. 그게 이전 노드의 successor가 됨.
    }
    
    TreeNode *y = p->parent;
    while (y != NULL && p == y->right) {
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
    
    while (q->left) q = q->left;
    do {
        printf("%c\n", q->data);
        q = tree_successor(q);
    } while (q);
    
    return 0;
}
