// Program to implement queue
#include <stdio.h> 
#include <stdlib.h> 
#include "head.h"  

  
// Create a new node 
struct plane* newNode(int k, int time) 
{ 
    struct plane* ele = (struct plane*)malloc(sizeof(struct plane)); 
    ele->key = k; 
    ele->time = time;
    ele->next = NULL; 
    return ele; 
} 
  
// To create a new queue 
Queue* createQ() 
{ 
    Queue* q = (Queue*)malloc(sizeof(Queue)); 
    q->front = q->rear = NULL; 
    return q; 
} 
  
// To add a new node with key k and time to queue 
void enQueue(Queue* q, int k, int time) 
{ 
    struct plane* temp = newNode(k, time);
    if (q->rear == NULL) 
    { 
        q->front = q->rear = temp; 
        return; 
    } 

    q->rear->next = temp; 
    q->rear = temp; 
} 
  
// Remove a node from given queue
void deQueue(Queue* q) 
{
    if (q->front == NULL) 
        return; 

    struct plane* temp = q->front; 
  
    q->front = q->front->next; 
 
    if (q->front == NULL) 
        q->rear = NULL; 
  
    free(temp); 
} 

// Check if queue is empty
bool empty(Queue *q)
{
    if(q->front == NULL)
        return true;
    return false;
}

// Returns the size of given queue
int size(Queue *q)
{
    int count = 0;
    struct plane* n = q->front;
    while(n!=NULL)
    {
        n = n->next; 
        count++;
    }
    return count;
}

// Increments the time of all nodes in given queue
void incrementTime(Queue *q)
{
    struct plane* n = q->front;
    while(n!=NULL)
    {
        (n->time)++;
        n = n->next;
    }
}