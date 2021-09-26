//
//  main.c
//  Data Structure
//  Assignment2-1
//  작성자 : 국어국문학과 1720047 이윤경
//

#include <stdio.h>
#define MAX_TERMS 10

typedef struct {
    int row;
    int col;
    int value;
} element;

typedef struct SparseMatrix {
    element data[MAX_TERMS];
    int rows;       //row size
    int cols;       //column size
    int terms;      //the number of elements
} SparseMatrix;


int main(void) {
    // Add B as an input.
    SparseMatrix B = { { {0, 3, 7}, {1, 0, 9}, {1, 5, 8}, {3, 0, 6}, {3, 1, 5}, {4, 5, 1}, {5, 2, 2} }, 6, 6, 7 };
    SparseMatrix BT = B;
    
    //transpose operation
    int i, j, temp;
    for (i=0 ; i<BT.terms ; i++) {
        temp = BT.data[i].row;
        BT.data[i].row = BT.data[i].col;
        BT.data[i].col = temp;
    }

    
    
    //print out B and B^T in a dense matrix for to check
    //whether the operation works correctly.
    
    int dense_B[B.rows][B.cols];
    int dense_BT[B.rows][B.cols];
    
    //initializing all values to 0
    for (i=0 ; i<B.rows ; i++) {
        for (j=0 ; j<B.cols ; j++) {
            dense_B[i][j] = 0;
            dense_BT[i][j] = 0;
        }
    }
    
    
    for (i=0 ; i<B.terms ; i++) {
        dense_B[B.data[i].row][B.data[i].col] = B.data[i].value;
        dense_BT[BT.data[i].row][BT.data[i].col] = BT.data[i].value;
    }
    
    for (i=0 ; i<B.rows ; i++) {
        for (j=0 ; j<B.rows ; j++) {
            printf("%d ", dense_B[i][j]);
        }
        printf("\n");
    }
    
    
    printf("\n");
    
    
    
    for (i=0 ; i<BT.rows ; i++) {
        for (j=0 ; j<BT.rows ; j++) {
            printf("%d ", dense_BT[i][j]);
        }
        printf("\n");
    }
    
    
    
    return 0;
}

