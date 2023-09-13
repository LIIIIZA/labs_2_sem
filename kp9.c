#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int value;
} Table;

void TablePrint(Table* t, int n) {
    printf("    key    |  value\n");
    printf("-----------------------\n");
    for (int i = 0; i < n; ++i) {
        printf("%10d |%10d\n", t[i].key, t[i].value);
    }
}

void ShakerSort(Table* t, int size) {
    int left = 0, right = size - 1;
    int flag = 1;
    Table tmp;
    while ((left < right) && flag > 0) {
        flag = 0;
        for (int i = left; i < right; ++i) {
            if (t[i].key > t[i+1].key) {
                tmp.key = t[i].key;
                tmp.value = t[i].value;
                t[i].key = t[i+1].key;
                t[i].value = t[i+1].value;
                t[i+1].key = tmp.key;
                t[i+1].value = tmp.value;
                flag = 1;
            }
        }
        --right;
        for (int i = right; i > left; --i) {
            if (t[i-1].key > t[i].key) {
                tmp.key = t[i].key;
                tmp.value = t[i].value;
                t[i].key = t[i-1].key;
                t[i].value = t[i-1].value;
                t[i-1].key = tmp.key;
                t[i-1].value = tmp.value;
                flag = 1;
            }
        }
        ++left;
    }
    
}

int BinarySearch(Table* t, int key, int left, int right) {
    int middle = (left + right) / 2;
    if (key == t[middle].key) {
        return middle + 1;
    }
    if (left >= right) {
        return (key > t[left].key) ? (left + 1) : left;
    }    
    if (key > t[middle].key) {
        return BinarySearch(t, key, middle + 1, right);
    }
    return BinarySearch(t, key, left, middle - 1);
}

void InsertionSort(Table* t, int size) {
    int newInd, tmpKey, tmpValue;
    for (int i = 1; i < size; ++i) {
        tmpKey = t[i].key;
        tmpValue = t[i].value;
        newInd = BinarySearch(t, tmpKey, 0, i - 1);
        for (int j = i - 1; j >= newInd; --j) {
            t[j + 1].key = t[j].key;
            t[j + 1].value = t[j].value;
        }
        t[newInd].key = tmpKey;
        t[newInd].value = tmpValue;
    }
}

int main(void) {
    int size, value, key;
    printf("print the number of elements ->  ");
    scanf("%d", &size);
    Table tableForShakerSort[size];
    Table tableForBinaryInsertion[size];
    for (int i = 0; i < size; ++i) {
        printf("\nline %d\n", i + 1);
        printf("print the key ->  ");
        scanf("%d", &key);
        tableForShakerSort[i].key = key;
        tableForBinaryInsertion[i].key = key;
        printf("print the value ->  ");
        scanf("%d", &value);
        tableForShakerSort[i].value = value;
        tableForBinaryInsertion[i].value = value;
    }
    printf("\nTable before sort\n");
    TablePrint(tableForShakerSort, size);
    printf("\nShaker sort\n");
    ShakerSort(tableForShakerSort, size);
    TablePrint(tableForShakerSort, size);
    printf("\nBinary insertion sort\n");
    InsertionSort(tableForBinaryInsertion, size);
    TablePrint(tableForBinaryInsertion, size);
    printf("\nprint key to find value -> ");
    scanf("%d", &key);
    value = tableForShakerSort[BinarySearch(tableForShakerSort,key,0,size-1)-1].value;
    printf("value -> %d", value);
    return 0;
}