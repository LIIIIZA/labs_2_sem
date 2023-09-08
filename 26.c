#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    Node *left;
    Node *right;
    Node *head;
} LinBidList;

LinBidList LinBidList_create() {
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

bool LinbidList_is_empty(LinBidList* list) {
    return (list->left->next == list->right);
}

void LinBidList_beginning(LinBidList* list) {
	if(!LinbidList_is_empty(list)) {
        list->head = list->left->next;
    }
    return;
}

void LinBidList_end(LinBidList* list) {
	if(!LinbidList_is_empty(list)) {
        list->head = list->right->prev;
    }
    return;
}

void LinBidList_find_by_ind(LinBidList* list, int ind) {
    LinBidList_beginning(list);
    for (int i = 1; i <= ind; ++i) {
        if (list->head->next == list->right) {
            printf("Too big index");
            return;
        }
        list->head = list->head->next;
    }
    return;
}

int LinBidList_size(LinBidList list) {
    LinBidList_beginning(&list);
    int count = 1;
    while (list.head->next != list.right) {
        list.head = list.head->next;
        count++;
    }
    return count;
}

void LinBidList_push_front(LinBidList list, int elem) {
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
        LinBidList_beginning(&list);
        list.left->next = newElem;
        newElem->prev = list.left;
        list.head->prev = newElem;
        newElem->next = list.head;
    }
    return;
}

void LinBidList_push_back(LinBidList list, int elem) {
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
        LinBidList_end(&list);
        list.right->prev = newElem;
        newElem->next = list.right;
        list.head->next = newElem;
        newElem->prev = list.head;
    }
    return;
}

void LinBidList_pop_back(LinBidList* list) {
    Node* elem;
    if (list->left->next != list->right) {
        LinBidList_end(list);
        elem = list->head;
        list->right->prev = list->head->prev;
        list->head->prev->next = list->right;
        list->head = list->head->prev;
        free(elem);
    }
    return;
}

void LinBidList_pop_front(LinBidList* list) {
    Node* elem;
    if (list->left->next != list->right) {
        LinBidList_beginning(list);
        elem = list->head;
        list->head->next->prev = list->left; 
        list->left->next = list->head->next;
        list->head = list->head->next;
        free(elem);
    }
    return;
}

void LinBidList_insert_by_index(LinBidList list, int ind, int elem) {
    Node* newElem;
    newElem = (Node*)malloc(sizeof(Node));
    newElem->value = elem;
    if (ind == 0) {
        LinBidList_push_front(list, elem);
        return;
    }
    if (ind == LinBidList_size(list)) {
        LinBidList_push_back(list, elem);
        return;
    }
    Node* tmp;
    tmp = list.head;
    LinBidList_beginning(&list);
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

void LinBidList_erase(LinBidList *list, int ind) {
	Node* elem;
    if (ind == 0) {
        LinBidList_pop_front(list);
        return;
    }
    if (ind == LinBidList_size(*list) - 1) {
        LinBidList_pop_back(list);
        return;
    }
    LinBidList_find_by_ind(list, ind);
    elem = list->head;
    list->head->prev->next= list->head->next;
    list->head->next->prev= list->head->prev;
    list->head = list->head->next;
    free(elem);
    return;
}

void LinBidList_print(LinBidList list) {
    printf("\n");
    LinBidList_beginning(&list);
    while (list.head != list.right) {
        printf("%d   ", list.head->value);
        list.head = list.head->next;
    }
    printf("\n");
    return;
}

void Procedure(LinBidList* list) {
    int elem;
    for (int indLastSorted = 0; indLastSorted < LinBidList_size(*list) - 1; ++indLastSorted) {
        LinBidList_find_by_ind(list, indLastSorted + 1);
        for (int indElemSort = indLastSorted + 1; indElemSort != 0; --indElemSort) {
            if (list->head->value >= list->head->prev->value) {
                break;
            }
            elem = list->head->value;
            LinBidList_erase(list, indElemSort);
            LinBidList_insert_by_index(*list, indElemSort-1, elem);
            LinBidList_find_by_ind(list, indElemSort - 1);
        }
    }
    return;
}

int main() {
    LinBidList list = LinBidList_create(); 
    int numOfElem, elem;
    printf("%d\n", LinbidList_is_empty(&list));
    printf("print number of elements ->  ");
    scanf("%d", &numOfElem);
    printf("print elements:\n");
    for (int i = 0; i < numOfElem; ++i) {
        printf("element %d - >  ", i);
        scanf("%d", &elem);
        LinBidList_push_back(list, elem);
    }
    printf("\n");
    Procedure(&list);
    LinBidList_print(list);

    return 0;
}