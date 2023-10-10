#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum COSMOS {
    asteroid,
    blackHole,
    comet,
    nebula,
    pulsar,
    quasar
} cosmos;

typedef struct Node{
    cosmos value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    Node *left;
    Node *right;
    Node *head;
} LinBidList;

LinBidList CreateLinBidList() {
	LinBidList list;
	list.left = (Node*) malloc(sizeof(Node));
	list.right = (Node*) malloc(sizeof(Node));

    list.left->prev = NULL;
    list.left->next = list.right;

    list.right->next= NULL;
    list.right->prev = list.left;

    list.head = list.left;
    return list;
}

void GoToBeginning(LinBidList* list) {
	if(list->left != list->right) {
        list->head = list->left->next;
    }
    return;
}

void GoToEnd(LinBidList* list) {
	if(list->left != list->right) {
        list->head = list->right->prev;
    }
    return;
}

int Length(LinBidList list) {
    GoToBeginning(&list);
    int count = 1;
    while (list.head->next != list.right) {
        list.head = list.head->next;
        count ++;
    }
    return count;
}

void AddToEnd(LinBidList list, cosmos elem) {
    Node* newElem;
    newElem = (Node*)malloc(sizeof(Node));
    newElem->value = elem;
    if (list.left->next == list.right){
        list.left->next = newElem;
        newElem->prev = list.left;
        list.right->prev = newElem;
        newElem->next = list.right;

    }
    else{
        GoToEnd(&list);
        list.right->prev = newElem;
        newElem->next = list.right;
        list.head->next = newElem;
        newElem->prev = list.head;
    }
    return;
}

void InsertByIndex(LinBidList list, int ind, cosmos elem) {
    Node* newElem;
    newElem = (Node*)malloc(sizeof(Node));
    newElem->value = elem;
    if (ind == 0) {
        GoToBeginning(&list);
        list.left->next = newElem;
        newElem->prev = list.left;
        list.head->prev = newElem;
        newElem->next = list.head;
        return;
    }
    if (ind == Length(list)) {
        AddToEnd(list, elem);
        return;
    }
    Node* tmp;
    tmp = list.head;
    GoToBeginning(&list);
    int i = 0;
    if(list.head->next != list.right){
            while(list.head->next != list.right && i < ind) { 
                list.head= list.head->next;
                i++;
            }
    }
    newElem->prev = list.head->prev;
    list.head->prev->next = newElem;
    newElem->next = list.head;
    list.head->prev = newElem;
    list.head = tmp;
    return;
}

void DelElemByIndex(LinBidList* list, int ind){
	Node *elem;
    if (ind == 0) {
        GoToBeginning(list);
        elem = list->head;
        list->head->next->prev = list->left; 
        list->left->next = list->head->next;
        list->head = list->head->next;
        free(elem);
        return;
    }
    GoToBeginning(list);
    int count = 1;
    while (list->head->next != list->right) {
        list->head = list->head->next;
        count ++;
    }
    if (ind == count - 1) {
        GoToEnd(list);
        elem = list->head;
        list->right->prev = list->head->prev;
        list->head->prev->next = list->right;
        list->head = list->head->prev;
        free(elem);
        return;
    }
    int step = 0;
    GoToBeginning(list);
    while (list->head->next != list->right) {
        if (step == ind){
            break;
        }
        list->head = list->head->next;
        step ++;
    }
    elem = list->head;
    list->head->prev->next= list->head->next;
    list->head->next->prev= list->head->prev;
    list->head = list->head->next;
    free(elem);
    return;
}

void RemoveAllList(LinBidList* list){
	Node *tmp;
    while(list->left != NULL){
        tmp = list->left;
        list->left = list->left->next;
        free(tmp);
    }
    return;
}

void DelEveryN(LinBidList* list, const int k, int index) { 
    if (list->head == list->right) {
        return;
    }
    if (index == k) {
        Node* tmp = list->head->next;
        Node* elem = list->head;
        list->head->prev->next = list->head->next;
        list->head->next->prev = list->head->prev;
        free(elem);
        list->head = tmp;
        index = 1;    
    }
    else {
        index ++;
        list->head = list->head->next;
    }
    DelEveryN(list, k, index);
}

void PrintSwitch(char elem) {
    switch (elem) {
            case asteroid :
                printf("asteroid  ");
                break;
            case blackHole :
                printf("blackHole  ");
                break;
            case comet :
                printf("comet  ");
                break;
            case nebula :
                printf("nebula  ");
                break;
            case pulsar :
                printf("pulsar  ");
                break;
            case quasar :
                printf("quasar  ");
                break;
            default :
                break;
        }
}

void PrintLinBidList(LinBidList list) {
    printf("\n");
    GoToBeginning(&list);
    while (list.head->next != list.right->next) {
        PrintSwitch(list.head->value);
        list.head = list.head->next;
    }
    printf("\n");
    return;
}

int main() {
    LinBidList list = CreateLinBidList();
    printf("print number of elements->  ");
    int num, len;
    scanf("%d", &num);
    printf("\nprint a for asteroid\nprint b for black hole\
    \nprint c for comet\nprint n for nebula\
    \nprint p for pulsar\nprint q for quasar\n\n");
    char elem;
    cosmos* arrayPtr = malloc(num * sizeof(cosmos));
    for (int i = 0; i < num; ++i) {
        printf("element %d ->  ", i);
        scanf("%c", &elem);
        if (elem == '\n') {
            scanf("%c", &elem);
        }
        switch (elem) {
            case 'a' :
                AddToEnd(list, asteroid);
                *(arrayPtr + i) = asteroid;
                break;
            case 'b' :
                AddToEnd(list, blackHole);
                *(arrayPtr + i) = blackHole;
                break;
            case 'c' :
                AddToEnd(list, comet);
                *(arrayPtr + i) = comet;
                break;
            case 'n' :
                AddToEnd(list, nebula);
                *(arrayPtr + i) = nebula;
                break;
            case 'p' :
                AddToEnd(list, pulsar);
                *(arrayPtr + i) = pulsar;
                break;
            case 'q' :
                AddToEnd(list, quasar);
                *(arrayPtr + i) = quasar;
                break;
            default:
                printf("\nWRONG VALUE\n");
                exit(-1);
                break;
        }
    }
    PrintLinBidList(list);
    len = Length(list);
    printf("\nlength of the list -> %d\n", len);
    printf("\nprint the index of new the value from 0 to %d ->  ", len);
    int ind;
    scanf("%d", &ind);
    if (ind > len || ind < 0) {
        printf("\nWRONG INDEX\n");
    }
    else {
        printf("\nprint a for asteroid\
        \nprint b for black hole\nprint c for comet\nprint n for nebula\nprint p for pulsar\
        \nprint q for quasar\n\nnew element ->  ");
        scanf("\n%c", &elem);
        switch (elem) {
            case 'a' :
                InsertByIndex(list, ind, asteroid);
                break;
            case 'b' :
                InsertByIndex(list, ind, blackHole);
                break;
            case 'c' :
                InsertByIndex(list, ind, comet);
                break;
            case 'n' :
                InsertByIndex(list, ind, nebula);
                break;
            case 'p' :
                InsertByIndex(list, ind, pulsar);
                break;
            case 'q' :
                InsertByIndex(list, ind, quasar);
                break;
            default:
                printf("\nWRONG VALUE\n\n");
                break;
        }
        PrintLinBidList(list);
    }
    len = Length(list);
    printf("\nlength of the list -> %d\n", len);
    printf("\nprint the index to delete the value from 0 to %d ->  ", len - 1);
    scanf("%d", &ind);
    if (ind < len && ind >= 0) {
        DelElemByIndex(&list, ind);
        PrintLinBidList(list);
    }
    else {
        printf("\nWRONG INDEX\n");
    }
    len = Length(list);
    printf("\nlength of the list -> %d\n", len);
    printf("\nprint the number k to delete every k element->  ");
    scanf("%d", &ind);
    if (ind > len || ind < 1) {
        printf("\nWRONG NUMBER\n");
    }
    else if (ind == 1) {
        RemoveAllList(&list);
        printf("\nALL LIST WAS DELETED\n");
        return 0;
    }
    else { 
        GoToBeginning(&list);
        DelEveryN(&list, ind, 1);
        PrintLinBidList(list);
    }
    len = Length(list);
    printf("\nlength of the list -> %d\n\n", len);
    printf("START ARRAY\n");
    for (int i = 0; i < num; ++i) {
        PrintSwitch(*(arrayPtr + i));
    }
    return 0;
}
