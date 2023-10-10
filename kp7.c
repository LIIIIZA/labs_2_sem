#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100

void PrintArray (int matr[], int count, int ind) {
    if (count == 1) {
        if (matr[ind] == 0) {
            printf("%d\n", matr[ind]);
            return;
        } 
        else {
            count = 0;
        }
    } 
    else {
        if (matr[ind] == 0) {
            ++count;
        }
    }
    printf("%d  ", matr[ind]);
    ++ind;
    PrintArray(matr, count, ind);
}

void PrintUsualMatrix(int matr[], int maxNumOfElem, int numOfColumns) {
    int count = 0;
    int lastValue = 0;
    for (int i = 0; i < 500; ++i) {
        if (count >= maxNumOfElem) {
            printf("%c", '\n');
            return;
        }
        if (matr[i] == 0) {
            if (matr[i+1] == 1) {
                i++;
                continue;
            }
            if (matr[i+1] == 0) {
                for (int j = lastValue + 1; j <= numOfColumns; ++j) {
                    printf("%5c", '0'); 
                    count++;
                }
                printf("%c", '\n');
                return;
            }
            if (matr[i+2] == 0) {
                for (int j = lastValue + 1; j <= numOfColumns; ++j) {
                    printf("%c", '0');
                    count++;
                }
                printf("%c", '\n');
                lastValue = 0;
                for (int j = 1; j <= numOfColumns; ++j) {
                    printf("%5c", '0');
                    count++;
                }
                printf("%c", '\n');
                count++;
                i += 3;
            }
            else {
                for (int j = lastValue + 1; j <= numOfColumns; ++j) {
                    printf("%5c", '0');
                    count++;
                }
                printf("%c", '\n');
                lastValue = 0;
                i++;
            }
        }
        else {
            for (int j = lastValue + 1; j < matr[i]; ++j) {
                    printf("%5c", '0');
                    count++;
            }
            printf("%5d", matr[i+1]);
            lastValue = matr[i];
            count++;
            i++;
        }
    }
}

int main() {
    
    int column;
    int matr[500] = {0};
    char line[MAX_LINE] = {' '};
    int matrInd = 0;
    FILE* f = fopen("matrix_for_kp7.txt", "r");
    int m, n;
    fgets(line, MAX_LINE, f);
    m = atoi(&line[0]);
    n = atoi(&line[2]);
    for (int i = 1; i <= m; ++i) {
        fgets(line, MAX_LINE, f);
        ++matrInd;
        matr[matrInd] = i;
        ++matrInd;
        column = 0;
        for (int j = 0; j < n*2; ++j) {
            if (line[j] == '\n') { break; }
            if (line[j] != ' ') {
                if (column == n) {
                    break;
                }
                column++;
                if (line[j] != '0') {
                    matr[matrInd] = column;
                    ++matrInd;
                    matr[matrInd] = atoi(&line[j]);
                    ++matrInd;
                }
            }
        }
    }
    fclose(f);
    matr[matrInd] = 0;
    ++matrInd;
    matr[matrInd] = 0;
    printf("Matrix in one vector:\n");
    PrintArray(matr, 0, 0);
    printf("Usual matrix:\n");
    PrintUsualMatrix(matr, n*m, n);
    int a, b;
    printf("Print numeric constants:\nconstant a ->  ");
    scanf("%d", &a);
    printf("constant b ->  ");
    scanf("%d", &b);
    int tmp[500] = {0};
    if (b == 0) {
        for (int i = 0; i < 500; ++i) {
            if (matr[i] == 0) {
                i += 1;
                continue;
            }
            i++;
            matr[i] = matr[i] * a;
        }
        for (int i = 0; i < n*m; ++i) {
            tmp[i] = matr[i];
        }
    }
    else {
        column = 0;
        int indTmp = 0;
        for (int i = 0; i < 500; ++i) {
            if (matr[i] == 0) {
                if (matr[i+1] == 0) {
                    for (int j = column; j <= n; ++j) {
                        tmp[indTmp] = j;
                        indTmp++;
                        tmp[indTmp] = b;
                        indTmp++;
                    }
                    tmp[indTmp] = matr[i];
                    indTmp++;
                    tmp[indTmp] = matr[i+1];
                    indTmp++;
                    break;
                }
                if (column != 0 && column != n + 1) {
                    for (int j = column; j <=n; ++j) {
                        tmp[indTmp] = j;
                        indTmp++;
                        tmp[indTmp] = b;
                        indTmp++;
                    }
                }
                tmp[indTmp] = matr[i];
                indTmp++;
                i++;
                tmp[indTmp] = matr[i];
                indTmp++;
                column = 1;
                if (matr[i+1] == 0) {
                    continue;
                }
                i++;
            }
            
            for (int j = column; j < matr[i]; ++j) {
                tmp[indTmp] = j;
                indTmp++;
                tmp[indTmp] = b;
                indTmp++;
            }
            tmp[indTmp] = matr[i];
            column = matr[i] + 1;
            indTmp++;
            i++;
            tmp[indTmp] = matr[i] * a + b;
            indTmp++;
        }
    }
    printf("Matrix after function in one vector:\n");
    PrintArray(tmp, 0, 0);
    printf("\nMatrix after function in usual way:\n");
    PrintUsualMatrix(tmp, n*m, n);
    return 0;
}
