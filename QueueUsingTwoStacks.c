#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/* structure of a stack node */
struct sNode {
  int data;
  struct sNode *next;
};

/* Function to push an item to stack*/
void push(struct sNode** top_ref, int new_data);
 
/* Function to pop an item from stack*/
int pop(struct sNode** top_ref);
int peek(struct sNode** top_ref);
 
/* structure of queue having two stacks */
struct queue {
    struct sNode* stack1;
    struct sNode* stack2;
};
 
/* Function to enqueue an item to queue */
void enQueue(struct queue* q, int x)
{
    push(&q->stack1, x);
}
 
/* Function to deQueue an item from queue */
int deQueue(struct queue* q)
{
    int x;
 
    /* If both stacks are empty then error */
    if (q->stack1 == NULL && q->stack2 == NULL) {
        printf("Q is empty");
        getchar();
        exit(0);
    }
 
    /* Move elements from stack1 to stack 2 only if
       stack2 is empty */
    if (q->stack2 == NULL) {
        while (q->stack1 != NULL) {
            x = pop(&q->stack1);
            push(&q->stack2, x);
        }
    }
 
    x = pop(&q->stack2);
    return x;
}
 
/* Function to push an item to stack*/
void push(struct sNode** top_ref, int new_data)
{
    /* allocate node */
    struct sNode* new_node = (struct sNode*)malloc(sizeof(struct sNode));
    if (new_node == NULL) {
        printf("Stack overflow \n");
        getchar();
        exit(0);
    }
 
    /* put in the data */
    new_node->data = new_data;
 
    /* link the old list off the new node */
    new_node->next = (*top_ref);
 
    /* move the head to point to the new node */
    (*top_ref) = new_node;
}
int pop(struct sNode** top_ref)
{
    int res;
    struct sNode* top;
 
    if (*top_ref == NULL) {
        printf("Stack underflow \n");
        getchar();
        exit(0);
    }
    else {
        top = *top_ref;
        res = top->data;
        *top_ref = top->next;
        free(top);
        return res;
    }
}

/* Function to peek an item from stack*/
int peek(struct sNode** top_ref)
{
    int res;
    struct sNode* top;
 
    /*If stack is empty then error */
    if (*top_ref == NULL) {
        printf("Stack underflow \n");
        getchar();
        exit(0);
    }
    else {
        res = (*top_ref)->data;
        return res;
    }
}

void display(struct queue* q){
    int x = 0;
 
    /* If both stacks are empty then error */
    if (q->stack1 == NULL && q->stack2 == NULL) {
        printf("Q is empty");
        getchar();
        exit(0);
    }
 
    /* Move elements from stack1 to stack 2 only if stack2 is empty */
    if (q->stack2 == NULL) {
        while (q->stack1 != NULL) {
            x = pop(&q->stack1);
            push(&q->stack2, x);
        }
    }
 
    x = peek(&q->stack2);
    printf("%d\n",x);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    int n = 0;
    scanf("%d", &n);
    struct queue* head= (struct queue*)malloc(sizeof(struct queue));
    head->stack1 = NULL;
    head->stack2 = NULL;
    while(n > 0)
    {
        int input = 0;
        int num = 0;
        scanf("%d", &input);
        switch(input){
            case 1:
                scanf("%d", &num);
                enQueue(head, num);
                break;
            case 2:
                deQueue(head);
                break;
            case 3:
                display(head);
                break;
        }
        n--;
    }
    
    return 0;
}
