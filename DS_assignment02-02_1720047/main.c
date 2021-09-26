//
//  main.c
//  main2
//
//  Created by YOONKYUNG LEE on 2021/09/26.
//

#include <stdio.h>
#include <stdlib.h>

#define LIMIT_A 2
#define LIMIT_B 3
#define LIMIT_C 4

double*** mem_alloc_3D_double(void) {
    double ***p;
    p = (double ***)malloc(sizeof(double**) * LIMIT_A);
        
    for (int i=0 ; i<LIMIT_A ; i++) {
        p[i] = (double **)malloc(sizeof(double*) * LIMIT_B);
        
        for (int j=0 ; j<LIMIT_B ; j++) {
            p[i][j] = (double*)malloc(sizeof(double) * LIMIT_C);
        }
    }
    
    for (int i=0 ; i<LIMIT_A ; i++) {
        for (int j=0 ; j<LIMIT_B ; j++) {
            for (int k=0 ; k<LIMIT_C ; k++) {
                p[i][j][k] = rand() % 100;
                printf("%5.f ", p[i][j][k]);
            }printf("\n");
        }printf("\n");
    }
    
    return p;
}


void addition_3D(double ***A, double ***B) {
    double C[LIMIT_A][LIMIT_B][LIMIT_C];
    
    for (int i=0 ; i<LIMIT_A ; i++) {
        for (int j=0 ; j<LIMIT_B ; j++) {
            for (int k=0 ; k<LIMIT_C ; k++) {
                C[i][j][k] = A[i][j][k] + B[i][j][k];
                printf("%5.f ", C[i][j][k]);
            } printf("\n");
        } printf("\n");
    }
}


int main(void) {
    //Define two matrices A and B using 'mem_alloc_3D_double';    
    printf("--3D Array A--\n");
    double *** A = mem_alloc_3D_double();
    printf("--3D Array B--\n");
    double *** B = mem_alloc_3D_double();
    
    
    
    //Perform addition of two matrices using ‘addition_3D()’
    printf("\n----Addition Result----\n");
    addition_3D(A, B);
    
    
    //Deallocate A and B
    for (int i=0 ; i<LIMIT_A ; i++) {
        for (int j=0 ; j<LIMIT_B ; j++) {
            
            free(A[i][j]);
            free(B[i][j]);
        }
        free(A[i]);
        free(B[i]);
    }
    free(A);
    free(B);
    printf("deallocation succeeded!\n");
    
    return 0;
}
