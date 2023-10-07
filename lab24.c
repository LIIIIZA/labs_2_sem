#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node_queue{
    char value;
    struct Node_queue* next;
};

typedef struct {
    int size;
    struct Node_queue* first;
    struct Node_queue* last;
} Queue;

Queue* Queue_create() {
    Queue* q = malloc(sizeof(Queue));
    q->first = q->last;
    q->size = 0;
}

void Queue_push(Queue* q, char elem) {
    struct Node_queue* new = malloc(sizeof(struct Node_queue));
    if (!new) {
        exit(-4);
    }
    new->value = elem;
    if (q->size == 0) {
        q->first = new;
        q->last = new;
    }
    else {
        q->last->next = new;
        q->last = q->last->next;
    }
    ++q->size;
}

char Queue_pop(Queue* q) {
    if (q->size != 0) {
        struct Node_queue* tmpPtr = q->first;
        char tmpVal = q->first->value;
        q->first = q->first->next;
        free(tmpPtr);
        --q->size;
        return tmpVal;
    }
   else {
    exit(-1);
   }
}

void Queue_destroy(Queue* q) {
    if (q->size == 0) {
        return;
    }
    q->last->next = 0;
    struct Node_queue* tmp = q->first;
    q->first = q->first->next;
    free(tmp);
    if (q->first) {
        Queue_destroy(q);
    }
    q->last = 0;
    q->size = 0;
}

void Queue_print(Queue* q) {
    printf("queue\n");
    struct Node_queue* tmp = q->first;
    for (int i = q->size; i > 0; i--) {
        printf("%c\n", tmp->value);
        tmp = tmp->next;
    }
}

struct Node_stack {
    char value;
    struct Node_stack* prev;
};

typedef struct {
    struct Node_stack* top;
    int size;
} Stack;

Stack* Stack_create() {
    Stack* s = malloc(sizeof(Stack));
    s->size = 0;
    return s;
}

void Stack_push(Stack* s, char elem) {
    struct Node_stack* new = malloc(sizeof(struct Node_stack));
    if (!new) {
        exit(-2);
    }
    new->value = elem;
    new->prev = s->top;
    s->top = new;
    ++s->size;
}

char Stack_pop(Stack* s) {
    if (s->size != 0) {
        struct Node_stack* tmp = s->top;
        char tmpVal = s->top->value;
        s->top = s->top->prev;
        --s->size;
        free(tmp);
        return tmpVal;
    }
    else {
        exit(-3);
    }
}

void Stack_destoy(Stack* s) {
    if (s->size == 0) {
        return;
    }
    struct Node_stack* tmp;
    while (s->top) {
        tmp = s->top;
        s->top = s->top->prev;
        free(tmp);
    }
    s->top = 0;
    s->size = 0;
}

void Stack_print(Stack* s) {
    struct Node_stack* tmp = s->top;
    printf("\nstack\n");
    for (int i = s->size; i > 0; --i) {
        printf("%c\n", tmp->value);
        tmp = tmp->prev;
    }
}

typedef struct _Node_tree {
    char value;
    struct _Node_tree* left;
    struct _Node_tree* right;
    struct _Node_tree* parent;
} Node_tree;

Node_tree* Node_tree_create(char val) {
    Node_tree* tmp = malloc(sizeof(Node_tree));
    tmp->value = val;
    tmp->parent = NULL;
    tmp->left = tmp->right = NULL;
    return tmp;
}

void Node_tree_delete(Node_tree* root) {
    if (root == NULL){
        return;
    } 
    Node_tree_delete(root->left);
    Node_tree_delete(root->right);
    printf("\n Deleting node: %c", root->value);
    free(root);
} 

Node_tree* Node_tree_print(Node_tree* root, int level) {
    if (root) {
        for (int i = level; i > 0; --i) {
            printf("%c", ' ');
        }
        printf("%c\n", root->value);
        Node_tree_print(root->left, level + 3);
        Node_tree_print(root->right, level + 3);
    }
}

int Priority(char operator) {
    switch (operator) {
        case '(':
            return 4;
        case ')':
            return 4;    
        case '^':
            return 3;
            break;
        case '*':
            return 2;
            break;
        case '/':
            return 2;
            break;
        case '+':
            return 1;
            break;
        case '-':
            return 1;
            break;
        default:
            break;
    }
    return -1;
}

bool IsOperand(char elem) {
    return (elem >= 'a' && elem <= 'z') || (elem >= 'A' && elem <= 'Z') || (elem >= '0' && elem <= '9');
}

bool IsOperator(char elem) {
    return (elem == '+') || (elem == '*') || (elem == '-') || (elem == '/') || (elem == '^');
}

bool IsOperatorWithoutMulti(char elem) {
    return (elem == '+') || (elem == '-') || (elem == '/') || (elem == '^');
}

void Dijkstra(Queue* qin, Queue* qout, Stack* s) {
    char elem, stackElem;
    bool leftBracket = false;
    while (qin->size != 0) {
        elem = Queue_pop(qin);
        if (IsOperand(elem)) {
            Queue_push(qout, elem);
        }
        else if (elem == '(') {
            Stack_push(s, elem);
            leftBracket = true;
        }
        else if (elem == ')') {
            if (!leftBracket) {
                exit(-5);
            }
            elem = Stack_pop(s);
            while (elem!='(') {
                Queue_push(qout, elem);
                elem = Stack_pop(s);
            }
            leftBracket = false;
        }       
        else {
            if (s->size == 0) {
                Stack_push(s, elem);
            }
            else if (Priority(elem) > Priority(s->top->value)) {
                Stack_push(s, elem);
            }
            else {
                while ((s->size!=0) && (Priority(elem) <= Priority(s->top->value)) && (s->top->value != '(')) {
                    stackElem = Stack_pop(s);
                    Queue_push(qout, stackElem);
                }
                Stack_push(s, elem);
            }
        }
    }
    while (s->size != 0) {
        stackElem = Stack_pop(s);
        Queue_push(qout, stackElem);
    }
}

void Dijkstra_to_tree(int s, Node_tree* trees[s], char arr[s]) {
    int indTrees = 0;
    for (int i = 0; i < s; ++i) {
        if (IsOperator(arr[i])) {
            Node_tree* elem = Node_tree_create(arr[i]);
            elem->right = trees[indTrees-1];
            elem->left = trees[indTrees-2];
            indTrees -= 2;
            trees[indTrees] = elem;
            indTrees++;
        }
        else {
            Node_tree* elem = Node_tree_create(arr[i]);
            trees[indTrees] = elem;
            indTrees++;
        }
    }
}

void Comparation(Node_tree* headLeft, Node_tree* headRight, Queue* q) {
    if (headRight == NULL || headLeft->value == '\n') {
        return;
    }
    if (IsOperand(headRight->value)) {
        if (headRight->value == headLeft->value) {
            Queue_push(q, headRight->value);
            headLeft->value = headRight->value = '\n';
            return;
        }
        Comparation(headLeft, headRight->left, q);
        Comparation(headLeft, headRight->right, q);
    } 
    else if (headRight->value == '*') {
        Comparation(headLeft, headRight->left, q);
        Comparation(headLeft, headRight->right, q);
    }
    return;
}

void LeftBranchTraversal(Node_tree* leftBranch, Node_tree* rightBranch, Queue* multiQueue) {
    if (leftBranch != NULL && leftBranch->value != '+' && leftBranch->value != '-' && 
    leftBranch->value != '/' && leftBranch->value != '^') {
        if (IsOperand(leftBranch->value)) {
            Comparation(leftBranch, rightBranch, multiQueue);
        }
        if (leftBranch->value != '\n') {
            LeftBranchTraversal(leftBranch->left, rightBranch, multiQueue);
            LeftBranchTraversal(leftBranch->right, rightBranch, multiQueue);
        }
    }
    return;
}

void AddMultToTree(Node_tree* MultTree[], Node_tree* tree, int size) {
    if (tree == NULL) {
        return;
    }
    int ind;
    for (ind = 0; ind < size; ++ind) {
        if (MultTree[ind]->value == '\n') {
            break;
        }
    }
    if (IsOperand(tree->value)) {
        Node_tree* elem = Node_tree_create(tree->value);
        if (ind > 0) {
            Node_tree* operator = Node_tree_create('*');
            operator->left = MultTree[ind-1];
            operator->right = elem;
            MultTree[ind-1] = operator;
        }
        else {
            MultTree[ind] = elem;
        }
    }
    else if (IsOperator(tree->value) && tree->value != '*') {
        Node_tree* elem = tree;
        if (ind > 0) {
            Node_tree* operator = Node_tree_create('*');
            operator->left = MultTree[ind-1];
            operator->right = elem;
            MultTree[ind-1] = operator;
        }
        else {
            MultTree[ind] = elem;
        }
        return;
    }
    AddMultToTree(MultTree, tree->left, size);
    AddMultToTree(MultTree, tree->right, size);
}

Node_tree* Multipliers(Node_tree* tree, int size) {
    if (tree->value != '+' || IsOperatorWithoutMulti(tree->left->value) || IsOperatorWithoutMulti(tree->right->value)) {
        printf("False");
        return tree;
    }
    Node_tree* headLeft = tree->left;
    Node_tree* headRight = tree->right;
    Queue* multiQueue = Queue_create();
    Node_tree* MultTree[size];
    for (int i = 0; i < size; ++i) {
        MultTree[i] = Node_tree_create('\n');
    }
    LeftBranchTraversal(headLeft, headRight, multiQueue);
    if (multiQueue->size == 0) {
        return tree;
    }
    AddMultToTree(MultTree, tree->left, size);
    Node_tree* sumLeftBranch = MultTree[0];
    if (sumLeftBranch->value == '\n') {
        sumLeftBranch->value = '1';
    }
    for (int i = 0; i < size; ++i) {
        MultTree[i] = Node_tree_create('\n');
    }
    AddMultToTree(MultTree, tree->right, size);
    Node_tree* sumRightBranch = MultTree[0];
    if (sumRightBranch->value == '\n') {
        sumRightBranch->value = '1';
    }
    Node_tree* sumTree = Node_tree_create('+');
    sumTree->left = sumLeftBranch;
    sumTree->right = sumRightBranch;
    Node_tree* multBranch = Node_tree_create('*');
    if (multiQueue->size == 1) {
        Node_tree* elem = Node_tree_create(Queue_pop(multiQueue));
        multBranch->left = elem;
        multBranch->right = sumTree;
        return multBranch;
    }
    Node_tree* headMultBranch = multBranch;
    while (multiQueue->size != 0) {
        if (multiQueue->size == 2) {
            Node_tree* elemLeft = Node_tree_create(Queue_pop(multiQueue));
            headMultBranch->left = elemLeft;
            Node_tree* elemRight = Node_tree_create(Queue_pop(multiQueue));
            headMultBranch->right = elemRight;
        }
        else {
            Node_tree* elemLeft = Node_tree_create('*');
            headMultBranch->left = elemLeft;
            Node_tree* elemRight = Node_tree_create(Queue_pop(multiQueue));
            headMultBranch->right = elemRight;
            headMultBranch = headMultBranch->left;
        }
    }
    Node_tree* newTree = Node_tree_create('*');
    newTree->left = multBranch;
    newTree->right = sumTree;
    return newTree;
}

int main() {
    Queue* qin = Queue_create();
    Queue* qout = Queue_create();
    Stack* s = Stack_create();
    char elem;
    int sizeQout;
    Queue_create(qin);
    Queue_create(qout);
    printf("print a mathematical expression without spaces\n->  ");
    scanf("%c", &elem);
    while (elem != '\n') {
        Queue_push(qin, elem);
        scanf("%c", &elem);
    }
    Dijkstra(qin, qout, s);
    sizeQout = qout->size;
    char DijkstraArr[sizeQout];
    for (int i = 0; i < sizeQout; ++i) {
        DijkstraArr[i] = Queue_pop(qout);
    }
    Node_tree* forDijkstra[sizeQout];
    for (int i = 0; i < sizeQout; ++i) {
        forDijkstra[i] = Node_tree_create('\n');
    }
    Dijkstra_to_tree(sizeQout, forDijkstra, DijkstraArr);
    Node_tree* DTree = forDijkstra[0];
    printf("\nBEFORE\n");
    Node_tree_print(DTree, 0);
    DTree = Multipliers(DTree, sizeQout);
    printf("\nAFTER\n");
    Node_tree_print(DTree, 0);
    Queue_destroy(qin);
    Queue_destroy(qout);
    Stack_destoy(s);
    Node_tree_delete(DTree);
    return 0;
}