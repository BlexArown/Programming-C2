#ifndef QUICKSORT_H
#define QUICKSORT_H

extern int C;
extern int M;

void FillInc(int n, int A[]);
void FillDec(int n, int A[]);
void FillRand(int n, int A[]);
int CheckSum(int n, int A[]);
void PrintMas(int n, int A[]);
void swap(int *a, int *b);
void QuickSort(int A[], int L, int R);
void quicksort_demo();

#endif

