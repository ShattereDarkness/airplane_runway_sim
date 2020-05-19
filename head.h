//File to store all the definitions of queue functions
#include<stdbool.h>

// Basic queue node to represent a single plane
struct plane {
    int key;
    int time;
    struct plane* next; 
}; 

// Structure of queue
// Front stores first node and rear stores the last node
typedef struct QueueQ { 
    struct plane *front, *rear;
}Queue; 

//To create new node
struct plane* newNode(int k, int time); 

// To create an empty queue 
Queue* createQ();

// To add a key k to queue 
void enQueue(Queue* q, int k, int time);

// Remove a key from given queue q 
void deQueue(Queue* q) ;

// To check if queue empty
bool empty(Queue *q);

//Returns size of queue
int size(Queue* q);

//Increments the time of each node in a queue
void incrementTime(Queue *q);