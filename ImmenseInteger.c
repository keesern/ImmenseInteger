/*
 *  Created by Kee Sern on 3/24/16.
 *  Copyright © 2016 Kee Sern. All rights reserved.
 */

#include<stdio.h>
#include<stdlib.h>

/* Linked list node */
struct node
{
    int data;
    struct node* next;
    struct node* prev;
};

typedef struct node* immense_int_t;

int getSize(struct node *node);
void swapPointer( immense_int_t* a, immense_int_t* b);
void createPointer(struct node** head_ref,int data);
immense_int_t add (immense_int_t first, immense_int_t second);
immense_int_t subtract (immense_int_t first, immense_int_t second);
void printList(struct node *node);
void destroyPointer(immense_int_t a);



/* Drier program to test above function */
int main(void)
{
    //Declaring 3 list, two input one output
    immense_int_t res = NULL;
    immense_int_t first = NULL;
    immense_int_t second = NULL;
    
    // Creating first list from user input
    char a;
    int notEnter = 1;
    while (notEnter) {
        scanf("%c",&a);
        if (a=='\n') {
            notEnter = 0;
        }else{
            int b = a-'0';
            createPointer(&first, b);
        }
    }
    //printList(first);
 
    //Creating second list from user input
    notEnter = 1;
    while (notEnter) {
        scanf("%c",&a);
        if (a=='\n') {
            notEnter = 0;
        }else{
            int b = a-'0';
            createPointer(&second, b);
        }
    }
    //printList(second);
    
    //Getting symbol to determine plus or minus equation
    char symbol = getchar();
    if (symbol=='+') {
        res = add(first, second);
    }else if(symbol=='-'){
        res = subtract(first, second);
    }
    
    //Printing result
    printList(res);
    
    //Free allocated memory
    destroyPointer(first);
    destroyPointer(second);
    destroyPointer(res);
    
    
    return 0;
}


//Return the size of the list
int getSize(struct node *node)
{
    int size = 0;
    while (node != NULL)
    {
        node = node->next;
        size++;
    }
    return size;
}

// A utility function to swap two pointers
void swapPointer( immense_int_t* a, immense_int_t* b )
{
    immense_int_t t = *a;
    *a = *b;
    *b = t;
}

/* Function to create a new node with given data */
void createPointer(struct node** head_ref,int data){
    immense_int_t new_node = (immense_int_t) malloc(sizeof(struct node));
    new_node->data = data;
    if ((*head_ref)==NULL) {
        new_node->next = NULL;
        new_node->prev = NULL;
        (*head_ref) = new_node;
    }else{
        immense_int_t temp = (*head_ref);
        while (temp->next!=NULL) {
            temp=temp->next;
        }
        temp->next = new_node;
        new_node->next = NULL;
        new_node->prev = temp;
    }
}



/* Adds contents of two linked lists and return the head node of resultant list */
immense_int_t add (immense_int_t first, immense_int_t second)
{
    int size1 = getSize(first);
    int size2 = getSize(second);
    
    //Ensuring the first list is always the largest
    if (size1 < size2)
        swapPointer(&first, &second);
    
    
    immense_int_t res = NULL; // res is head node of the resultant list
    immense_int_t temp1 = first, temp2= second;
    int carry = 0;
    
    //Calculating from the last digit of the link list
    while(temp1->next!=NULL){
        temp1=temp1->next;
    }
    while(temp2->next!=NULL){
        temp2=temp2->next;
    }
    
    //While first list is not empty continue addition
    while (temp1) {
        immense_int_t new_node = (immense_int_t) malloc(sizeof(struct node));
        //Addition calculation method
        if (temp2) {
            new_node->data = temp1->data + temp2->data + carry;
        }else{
            new_node->data = temp1->data + carry;
        }
        
        //Carry over digit larger then 10
        if (new_node->data>=10) {
            new_node->data -=10;
            carry=1;
        }else{
            carry=0;
        }
        
        //Adding to resultant list
        if (res==NULL) {
            new_node->next=NULL;
            new_node->prev=NULL;
            res = new_node;
        }else{
            new_node->next = res;
            new_node->prev=NULL;
            res->prev=new_node;
            res=new_node;
        }
        
        //Ensuring the carry over of the largest digit location
        if (carry==1 && temp1->prev==NULL) {
            immense_int_t new_node = (immense_int_t) malloc(sizeof(struct node));
            new_node->data = 1;
            new_node->next = res;
            new_node->prev=NULL;
            res->prev=new_node;
            res=new_node;
        }
        
        
        temp1=temp1->prev;
        if (temp2) {
            temp2=temp2->prev;
        }
    }
    return res;
}




/* Adds contents of two linked lists and return the head node of resultant list */
immense_int_t subtract (immense_int_t first, immense_int_t second)
{
    
    int size1 = getSize(first);
    int size2 = getSize(second);
    
    //Ensuring the first list is the largest
    if (size1 < size2)
        swapPointer(&first, &second);
    
    immense_int_t res = NULL; // res is head node of the resultant list
    struct node *temp1 = first, *temp2= second;
    int borrow = 0;
    
    //Calculating from the last digit location
    while(temp1->next!=NULL){
        temp1=temp1->next;
    }
    while(temp2->next!=NULL){
        temp2=temp2->next;
    }
    
    //Run While list 1 is not finish
    while (temp1) {
        //Creating a new node to store result
        immense_int_t new_node = (immense_int_t) malloc(sizeof(struct node));
        //subtraction method calculation
        if (temp2) {
            new_node->data = temp1->data - temp2->data-borrow;
        }else{
            new_node->data = temp1->data - borrow;
        }
        
        //Adding node to the resultant list
        if (res==NULL) {
            new_node->next=NULL;
            new_node->prev=NULL;
            res = new_node;
        }else{
            new_node->next = res;
            new_node->prev=NULL;
            res->prev=new_node;
            res=new_node;
        }
        
        //Borrowing from the front digit if its not large enuough
        if (new_node->data<0) {
            new_node->data +=10;
            borrow=1;
        }else{
            borrow = 0;
        }
        
        temp1=temp1->prev;
        if (temp2) {
            temp2=temp2->prev;
        }
        
    }
    
    //Eliminating leadings zero
    while(res->next!=NULL && res->data==0) {
        res = res->next;
    }
    
    return res;
}



// A utility function to print a linked list
void printList(struct node *node)
{
    while(node != NULL)
    {
        printf("%d", node->data);
        node = node->next;
    }
    printf("\n");
}


//Function to free pointers
void destroyPointer(immense_int_t a){
    immense_int_t node = a;
    while (node != NULL){
        immense_int_t temp = node;
        node = node->next;
        temp->next=NULL;
        temp->prev=NULL;
        free(temp);
    }
    free(node);
}
