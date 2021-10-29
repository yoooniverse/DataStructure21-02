//
//  main.c
//  DS_assignment05-03_1720047
//  Assignment5-3
//  작성자 : 국어국문학과 1720047 이윤경
//
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <stdafx.h> 오류 발생으로 인해 삭제

typedef struct TreeNode {
    int key;
    struct TreeNode *left, *right;
} TreeNode;


//                       35
//          18                 68
//   7             26                   99
//3     12     22         30
//    10          24

TreeNode n12 = { 24, NULL, NULL };
TreeNode n11 = { 10, NULL, NULL };
TreeNode n10 = { 30, NULL, NULL };
TreeNode n9 = { 22, NULL, &n12 };
TreeNode n8 = { 12, &n11, NULL };
TreeNode n7 = { 3,  NULL, NULL };
TreeNode n6 = { 99, NULL, NULL };
TreeNode n5 = { 26, &n9, &n10 };
TreeNode n4 = { 7,  &n7, &n8 };
TreeNode n3 = { 68, NULL, &n6 };
TreeNode n2 = { 18, &n4, &n5 };
TreeNode n1 = { 35, &n2, &n3 };



// Insert the key into the binary search tree root.
// If key is already in root, it is not inserted.
void insert_node(TreeNode **root, int key)
{
    TreeNode *p, *t;// p: parent node, t: current node
    TreeNode *n;// n: new node to be inserted
    t = *root;
    p = NULL;
    // Search first
    while (t != NULL) {
        if (key == t->key) {
            printf("The same key exists in the tree.\n");
            return;
        }
        p = t;
        if (key < t->key) t = t->left;
        else t = t->right;
    }
    // Since the key is not in the tree, insertion is possible.
    n = (TreeNode *)malloc(sizeof(TreeNode));
    if (n == NULL) return;
    n->key = key;
    n->left = n->right = NULL;

    if (p != NULL)
        if (key < p->key)
            p->left = n;
        else p->right = n;
    else *root = n;
}

// Deletion in binary search tree
void delete_node(TreeNode **root, int key)
{
    TreeNode *p, *child, *pre, *pre_p, *t;
    // search node t with key, p: t's parent
    p = NULL;
    t = *root;
    while (t != NULL && t->key != key) {
        p = t;
        t = (key < t->key) ? t->left : t->right;
    }
    // If t is NULL at the end, there is no key in the tree
    if (t == NULL) {
        printf("key is not in the tree");
        return;
    }

    // Case 1
    if ((t->left == NULL) && (t->right == NULL)) {
        if (p != NULL) {
            if (p->left == t)
                p->left = NULL;
            else p->right = NULL;
        }
        // If the parent node is NULL, the node to be deleted is the root
        else
            *root = NULL;
    }

    // Case 2
    else if ((t->left == NULL) || (t->right == NULL)) {
        child = (t->left != NULL) ? t->left : t->right;
        if (p != NULL) {
            if (p->left == t)
                p->left = child;
            else p->right = child;
        }
        // If the parent node is NULL, the node to be deleted is the root
        else
            *root = child;
    }
    
    
    //여기가 고쳐야 하는 부분
    
    // Case 3
    // t : 지우고자 하는 값의 노드
    // 지우고자 하는 노드의 이전 노드(predecessor)를 찾아야 함
    else {
        // Find the predecessor at left subtree
        pre_p = t;
        pre = t->left; //왼쪽 서브트리로 지정한 다음
        // Keep moving to the right and find the predecessor
        while (pre->right != NULL) {
            pre_p = pre;
            pre = pre->right;
        }
        //pre_p->right = pre->left;
        if (pre_p->right == pre)
            pre_p->right = pre->left;
        else
            pre_p->left = pre->left;
        t->key = pre->key;
        t = pre;
    }
//    free(t);
}



void inorder(TreeNode *root) {
    if (root) {
        inorder(root->left); // Left subtree
        printf("%d\t", root->key); // Visit root node
        inorder(root->right);// Right subtree
    }
}

int main(void)
{
    TreeNode *root = &n1;

    printf("Binary tree\n");
    inorder(root);
    printf("\n\n");

    delete_node(&root, 18);
    delete_node(&root, 35);
    delete_node(&root, 7);


    printf("Binary tree\n");
    inorder(root);
    printf("\n\n");
}

