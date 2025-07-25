#include <stdio.h>
#include <stdlib.h>
#define INVALID -1
int totalTime = 0;
int leftSize = 0;
int rightSize = 0;
typedef struct Queue Queue;
typedef struct Node Node;
typedef struct Group Group;
// struct of Group
struct Group
{
    long long int s, a, p, fin;
};
struct Node
{
    struct Group data;
    struct Node *next;
};
// Queue implemented using a circular
// Linked List
struct Queue
{
    Node *tail;
};
// Sort an array of groups in increasing order of arrives
void sort(struct Group *array, int size);
// Create a node with a new group as data
// The node is for a circular linked list
Node *newNode(struct Group newGroup);
// Add a group to the tail of a circular linked list
// Return the resulting tail
Node *addTail(Node *tail, struct Group newGroup);
// Remove the head node of a circular linked list
// Return the resulting tail
Node *removeHead(Node *tail); // Node * removeHead(Node * tail, Group new Group); was given to us void print(Group data);
// Queue Prototypes
Group front(Queue *q);
Queue *createQueue();
void enqueue(Queue *q, struct Group data);
void dequeue(Queue *q);
void cleanQueue(Queue *q);
int main()
{
    int i, n, lAmount = 0, rAmount = 0;
    // Making 2 Queues
    Queue *leftQ = createQueue();
    Queue *rightQ = createQueue();
    scanf("%d", &n);
    // dynamically allocates memory for array of struct Groups
    struct Group *data = (Group *)calloc(n, sizeof(Group));
    // takes in input for the struct Groups under the name of data
    for (i = 0; i < n; i++)
    {
        scanf("%lld %lld %lld", &data[i].s, &data[i].a, &data[i].p);
        data[i].fin = data[i].p + data[i].a;
    }
    sort(data, n);
    for (i = 0; i < n; i++)
    {
        while (data[i].a > (front(leftQ).a + front(leftQ).p) && lAmount > 0)
        {
            leftSize -= front(leftQ).s;
            totalTime += front(leftQ).p * front(leftQ).s;
            dequeue(leftQ);
            lAmount--;
        }
        while (data[i].a > (front(rightQ).a + front(rightQ).p) && rAmount > 0)
        {
            rightSize -= front(rightQ).s;
            totalTime += front(rightQ).p * front(rightQ).s;
            dequeue(rightQ);
            rAmount--;
        }
        // adds a group to the leftQ when there are less people in it
        if (leftSize <= rightSize)
        {
            enqueue(leftQ, data[i]);
            leftSize += data[i].s;
            lAmount++;
            if (lAmount = 1)
            {
            }
            else
            {
                data[i].p = (data[i - 1].p + data[i - 1].a) - data[i].a;
            }
        }
        // adds a group to the rightQ when there are less people in it
        if (rightSize < leftSize)
        {
            enqueue(rightQ, data[i]);
            rightSize += data[i].s;
            rAmount++;
            if (rAmount = 1)
            {
            }
            else
            {
                data[i].p = (data[i - 1].p + data[i - 1].a) - data[i].a;
            }
        }
    }
    // empties the LeftQ
    while (leftQ->tail != NULL)
    {
        totalTime += front(leftQ).s * front(leftQ).p;
        dequeue(leftQ);
        lAmount--;
    }
    // empties the rightQ
    while (rightQ->tail != NULL)
    {
        totalTime += front(rightQ).s * front(rightQ).p;
        dequeue(rightQ);
        rAmount--;
    }
    printf("%d", totalTime);
    free(data);
    return 0;
}
// Merge Sort function
void sort(struct Group *arr, int size)
{
    if (size <= 1)
    {
        return;
    }
    sort(arr, size / 2);
    sort(arr + size / 2, size - size / 2);
    Group *tmp = calloc(size, sizeof(Group));
    // merge the values in both halves into the tmp array
    long long int frontPointer = 0;
    long long int backPointer = size / 2;
    long long int mergePointer = 0;
    while (mergePointer < size)
    {
        if (frontPointer == size / 2)
        {
            // Front is empty
            tmp[mergePointer] = arr[backPointer];
            mergePointer++;
            backPointer++;
        }
        else if (backPointer == size)
        {
            // Back is empty
            tmp[mergePointer] = arr[frontPointer];
            mergePointer++;
            frontPointer++;
        }
        else
        {
            // Neither are empty compare the front of both halves and use smallest
            value if (arr[frontPointer].a < arr[backPointer].a)
            {
                tmp[mergePointer] = arr[frontPointer];
                mergePointer++;
                frontPointer++;
            }
            else
            {
                tmp[mergePointer] = arr[backPointer];
                mergePointer++;
                backPointer++;
            }
        }
    }
    // Copy the merged array into the final array
    for (int i = 0; i < size; i++)
        arr[i] = tmp[i];
    free(tmp);
}
void print(struct Group data)
{
    printf("%lld %lld %lld", data.s, data.a, data.p);
}
// Circular Linked List functions
Node *createNode(struct Group newGroup)
{
    Node *result = (Node *)malloc(sizeof(Node));
    result->data = newGroup;
    result->next = result;
    return result;
}
Node *addTail(Node *tail, struct Group newGroup)
{
    if (tail == NULL)
    {
        return createNode(newGroup);
    }
    Node *oldTail = tail;
    Node *oldHead = oldTail->next;
    Node *newTail = createNode(newGroup);
    // Adjust pointers
    oldTail->next = newTail;
    newTail->next = oldHead;
    // Return the resulting tail
    return newTail;
}
Node *removeHead(Node *tail)
{
    // Empty list case
    if (tail == NULL)
    {
        return NULL;
    }
    // 1 node list case
    if (tail == tail->next)
    {
        free(tail);
        // the resulting is empty
        return NULL;
    }
    // More than 1 node
    Node *oldTail = tail;
    Node *oldHead = tail->next;
    Node *newHead = oldHead->next;
    // Free the memory to remove
    free(oldHead);
    // Adjust pointers
    oldTail->next = newHead;
    // Return the resulting tail
    return oldTail;
}
// Queue functions
Queue *createQueue()
{
    Queue *result = (Queue *)malloc(sizeof(Queue));
    result->tail = NULL;
    return result;
}
Group front(Queue *q)
{
    struct Group g1;
    g1.a = -1;
    g1.s = -1;
    g1.p = -1;
    if (q == NULL)
        return g1;
    if (q->tail == NULL)
        return g1;
    if (q->tail->next == NULL)
    {
        printf("SADNESS!\n");
        return g1;
    }
    return q->tail->next->data;
}
// Adds to the back of the queue
void enqueue(Queue *q, struct Group data)
{
    q->tail = addTail(q->tail, data);
} // Remove the front of the queue
void dequeue(Queue *q)
{
    q->tail = removeHead(q->tail);
}