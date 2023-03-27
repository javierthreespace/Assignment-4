#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int extraMemoryAllocated;

void merge(int pData[], int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  int *Left = (int *)malloc(n1 * sizeof(int));
  int *Right = (int *)malloc(n2 * sizeof(int));
 
  extraMemoryAllocated += n1 + n2;

  for (i = 0; i < n1; i++)
    Left[i] = pData[l + i];
  for (j = 0; j < n2; j++)
    Right[j] = pData[m + 1 + j];

  i = 0;
  j = 0;
  k = l;

  while (i < n1 && j < n2) {
    if (Left[i] <= Right[j]) {
      pData[k] = Left[i];
      i++;
    } else {
      pData[k] = Right[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    pData[k] = Left[i];
    i++;
    k++;
  }

  while (j < n2) {
    pData[k] = Right[j];
    j++;
    k++;
  }

  free(Left);
  free(Right);
}

void mergeSort(int pData[], int l, int r) {
  int m;

  if (l < r) {
    m = (l + r) / 2;

    mergeSort(pData, l, m);
    mergeSort(pData, m + 1, r);

    merge(pData, l, m, r);
  }
}

void insertionSort(int *pData, int n) {
  int i, item, j;

  for (i = 1; i < n; i++) {
    item = pData[i];
    j = i - 1;
    while (j >= 0 && pData[j] > item) {
      pData[j + 1] = pData[j];
      j = j - 1;
    }
    pData[j + 1] = item;
  }
}

void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

void bubbleSort(int *pData, int n) {
  int i, j;

  for (i = 0; i < n - 1; i++)
    for (j = 0; j < n - i - 1; j++)
      if (pData[j] > pData[j + 1])
        swap(&pData[j], &pData[j + 1]);
}

void selectionSort(int *pData, int n) {
  int i, j, count = 0;
  int minIndex, temp;

  for (i = 0; i < n - 1; i++) {
    minIndex = count;
    for (j = count; j < n; j++) {
      if (pData[j] < pData[minIndex])
        minIndex = j;
    }
    temp = pData[count];
    pData[count] = pData[minIndex];
    pData[minIndex] = temp;
    count++;
  }
}

int parseData(char *inputFileName, int **ppData) {
  FILE *inFile = fopen(inputFileName, "r");
  int dataSz = 0;
  *ppData = NULL;

  if (inFile) {
    fscanf(inFile, "%d\n", &dataSz);

    int *aPtr = (int *)malloc(sizeof(int) * dataSz);
    *ppData = (int *)malloc(sizeof(int) * dataSz);

    for (int i = 0; i < dataSz; i++)
      fscanf(inFile, "%d ", &((*ppData)[i]));
  }

  return dataSz;
}

void printArray(int pData[], int dataSz) {
  int i, sz = dataSz - 100;
  printf("\tData:\n\t");
  for (i = 0; i < 100; ++i) {
    printf("%d ", pData[i]);
  }
  printf("\n\t");

  for (i = sz; i < dataSz; ++i) {
    printf("%d ", pData[i]);
  }
  printf("\n\n");
}

int main(void) {
  clock_t start, end;
  int i;
  double cpu_time_used;
  char *fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};

  for (i = 0; i < 3; ++i) {
    int *pDataSrc, *pDataCopy;
    int dataSz = parseData(fileNames[i], &pDataSrc);

    if (dataSz <= 0)
      continue;

    pDataCopy = (int *)malloc(sizeof(int) * dataSz);

    printf("---------------------------\n");
    printf("Dataset Size : %d\n", dataSz);
    printf("---------------------------\n");

    printf("Selection Sort:\n");
    memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
    extraMemoryAllocated = 0;
    start = clock();
    selectionSort(pDataCopy, dataSz);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
    printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
    printArray(pDataCopy, dataSz);

    printf("Insertion Sort:\n");
    memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
    extraMemoryAllocated = 0;
    start = clock();
    insertionSort(pDataCopy, dataSz);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
    printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
    printArray(pDataCopy, dataSz);

    printf("Bubble Sort:\n");
    memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
    extraMemoryAllocated = 0;
    start = clock();
    bubbleSort(pDataCopy, dataSz);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
    printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
    printArray(pDataCopy, dataSz);

    printf("Merge Sort:\n");
    memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
    extraMemoryAllocated = 0;
    start = clock();
    mergeSort(pDataCopy, 0, dataSz - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
    printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
    printArray(pDataCopy, dataSz);

    free(pDataCopy);
    free(pDataSrc);
  }
}