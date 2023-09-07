#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_LINE_LEN 250
#define NUMBER_OF_STUDENTS 20

typedef struct PERSON {
    char surname[20];
    char initialsFirst[2];
    char initialsSec[2];
    char group[3];
    int marks[4];
    float averageMark;
} person;

void InsertSort(person p[], int n) {
    int k;
    person tmp;
    for (int i = n - 1; i > -1; --i) {
        k = i;
        while (k < n && p[k-1].averageMark < p[k].averageMark) {
            tmp =  p[k-1];
            p[k-1] = p[k];
            p[k] = tmp;
            k++;
        }   
    }
}

int main() {
    person p[NUMBER_OF_STUDENTS];
    char line[MAX_LINE_LEN];
    char filename[] = "C:\\Users\\asus\\Desktop\\Labs\\info.csv";
    int rank;
    printf("How much students do you need?\nPrint a number from 1 to 20 ->  ");
    scanf("%d", &rank);
    if (rank > 20 || rank < 1) {
        printf("Wrong number");
        return -1;
    }
    float aver;
    FILE* file_write = fopen("C:\\Users\\asus\\Desktop\\Labs\\file_for_kp6.txt", "w");
    FILE* students = fopen(filename, "r");
    if (!file_write) {
        perror("Can't open file to write");
        return 1;
    }
    if (!students) {
        perror("Can't open a file to read");
        return 1;
    }

    fgets(line, MAX_LINE_LEN, students);
    char inf[MAX_LINE_LEN];
    int indP, indLine;
    for (int numberOfStudent = 0; numberOfStudent < NUMBER_OF_STUDENTS; ++numberOfStudent) {
        fgets(line, MAX_LINE_LEN, students);
        indP = 0; 
        indLine = 0;   
        aver = 0; 
        while (line[indLine] != ',') {
            inf[indP] = line[indLine];
            ++indLine;
            ++indP;
        }  
        for (int j = 0; j < indP; ++j) {
            p[numberOfStudent].surname[j] = inf[j];
        }
        for (int j = indP; j < 20; ++ j) {
            p[numberOfStudent].surname[j] = ' ';
        } 
        ++indLine;
        for (int j = 0; j < 2; ++j) {
            p[numberOfStudent].initialsFirst[j] = line[indLine];
            ++indLine;
        }
        for (int j = 0; j < 2; ++j) {
            p[numberOfStudent].initialsSec[j] = line[indLine];
            ++indLine;
        }
        indP = 0; 
        ++indLine;
        while(line[indLine] != ',') {
            inf[indP] = line[indLine];
            ++indLine;
            ++indP;
        }
        for(int j = 0; j < indP; ++j) {
            p[numberOfStudent].group[j] = inf[j];
        }
        indP = 0; 
        for (int k = 0; k < 4; ++k) {
            ++indLine;
            char* forAtoi;
            forAtoi = &line[indLine];
            p[numberOfStudent].marks[k] = atoi(forAtoi);
            aver += p[numberOfStudent].marks[k];
            ++indLine;
        }
        aver /= 4;
        p[numberOfStudent].averageMark = aver;
    }
    InsertSort(p, NUMBER_OF_STUDENTS);
    fprintf(file_write, "%d students with the best average grade\n", rank);
    for (int i = 0; i < rank; ++i) {
        for (int j = 0; j < 20; ++j) {
            fprintf(file_write, "%c", p[i].surname[j]);
        }
        for (int j = 0; j < 2; ++j) {
            fprintf(file_write, "%c", p[i].initialsFirst[j]);
        }
        for (int j = 0; j < 2; ++j) {
            fprintf(file_write, "%c", p[i].initialsSec[j]);
        }
        fprintf(file_write, "   ");
        for (int j = 0; j < 3; ++j) {
            fprintf(file_write, "%c", p[i].group[j]);
        }
        fprintf(file_write, "  %.2f", p[i].averageMark);
        fprintf(file_write, "\n");
    }
    fclose(students);
    fclose(file_write);
    
    return 0;
}