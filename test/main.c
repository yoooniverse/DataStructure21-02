////
////  main.c
////  test
////
////  Created by YOONKYUNG LEE on 2021/10/13.
////
//// linked_stack.cpp : Defines the entry point for the console application.
////

#if 0


#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef int element;

typedef struct StackNode {
    element item;
    struct StackNode *link;
} StackNode;

typedef struct {
    StackNode *top;
} LinkedStackType;

//
void init(LinkedStackType *s)
{
    s->top = NULL;
}
//
int is_empty(LinkedStackType *s)
{
    return (s->top == NULL);
}

void push(LinkedStackType *s, element item)
{
    struct StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation error\n");
            return;
    }

    else {
        temp->item = item;
        temp->link = s->top;
        s->top = temp;
    }
}

element pop(LinkedStackType *s)
{
    if (is_empty(s)) {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }
    else {
        StackNode *temp = s->top;
        int item = temp->item;
        s->top = s->top->link;
        free(temp);
        return item;
    }
}

element peek(LinkedStackType *s)
{
    if (is_empty(s)) {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }
    else {
        return s->top->item;
    }
}

void main()
{
    LinkedStackType s;
    init(&s);
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);


    printf("%d\n", pop(&s));
    printf("%d\n", pop(&s));
    printf("%d\n", pop(&s));
}

#endif


#if 0
//
//
// Simulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define MAX_QUEUE_SIZE    100


typedef struct element {
    int id;
    int arrival_time;
    int service_time;
} element;         // Customer structure

typedef struct QueueType {
    element  queue[MAX_QUEUE_SIZE];
    int  front, rear;
} QueueType;
QueueType queue;

// Real random number generation function between 0 and 1
double random() {
    return rand() / (double)RAND_MAX;
}

// Various state variables needed for simulation
int duration = 10; // Simulation time
double arrival_prob = 0.7; // Average number of customers arriving in one time unit
int max_serv_time = 5; // maximum service time for one customer
int clock;

// Results of the simulation
int customers; // Total number of customers
int served_customers; // Number of customers served
int waited_time; // Time the customers waited

// Empty state detection function
int is_empty(QueueType * q)
{
    return (q->front == q->rear);
}
// Full state detection function
int is_full(QueueType * q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// Insert function
void enqueue(QueueType * q, element item)
{
    if (is_full(q))
        printf("Queue is full\n");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}
// delete function
element dequeue(QueueType * q)
{
    if (is_empty(q))
        printf("Queue is empty\n");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

// Generate a random number.
// If it is smaller than °Æarrival_prov°Ø, assume that new customer comes in the bank.
int is_customer_arrived()
{
    if (random() <arrival_prob)
        return true;
    else return false;
}
// Insert newly arrived customer into queue
void insert_customer(int arrival_time)
{
    element customer;

    customer.id = customers++;
    customer.arrival_time = arrival_time;
    customer.service_time = (int)(max_serv_time * random()) + 1;
    enqueue(&queue, customer);
    printf("Customer %d comes in %d minutes. Service time is %d minutes.\n", customer.id, customer.arrival_time, customer.service_time);
}

// Retrieve the customer waiting in the queue and return the customer's service time.
int remove_customer()
{
    element customer;
    int service_time = 0;

    if (is_empty(&queue)) return 0;
    customer = dequeue(&queue);
    service_time = customer.service_time - 1;
    served_customers++;
    waited_time += clock - customer.arrival_time;
    printf("Customer %d starts service in %d minutes. Wait time was %d minutes.\n", customer.id, clock, clock - customer.arrival_time);
    return service_time;
}


// Print the statistics.
void print_stat()
{
    printf("Number of customers served = %d\n", served_customers);
    printf("Total wait time =% d minutes\n", waited_time);
    printf("Average wait time per person = %f minutes\n",
        (double)waited_time / served_customers);
    printf("Number of customers still waiting = %d\n", customers - served_customers);
}


// Simulation program
void main()
{
    int service_time = 0;

    clock = 0;
    while (clock < duration) {
        clock++;
        printf("Current time=%d\n", clock);
        if (is_customer_arrived()) {
            insert_customer(clock);
        }

        // Check if the customer who is receiving the service is finished.
        if (service_time > 0)    // the customer is receiving service
            service_time--;

        // no customer is receiving service.
        // So, take out a customer from the queue and start the service.
        else {
            service_time = remove_customer();
        }
    }
    print_stat();
}



#endif

#if 0
//참고한 사이트 교수님이 주신 코드랑 거의 유사하다.
//http://nospblog.blogspot.com/2013/12/data-structure-3-4-server.html



#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FALSE 0
#define TRUE 1
#define MAX_QUEUE_SIZE 100

typedef struct {
    int id; // 고객 고유 번호. 들어오는 순서대로 번호표를 받는다고 생각하면 된다.
    int arrival_time; // 고객 도착 시간
    int service_time; // 고객에게 걸리는 서비스 시간
} element;

typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QueueType;

QueueType q; // 전역 변수로 설정

void error(char *message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init(QueueType *q){
    q->front = 0;
    q->rear = 0;
}

int is_empty(QueueType *q){
    return q->front == q->rear;
}

int is_full(QueueType *q){
    return (q->rear+1) % MAX_QUEUE_SIZE == q->front;
}

void enqueue(QueueType *q, element item){
    if (is_full(q)) error("q is full");
    q->rear = (q->rear+1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}

element dequeue(QueueType *q){
    if (is_empty(q)) error("q is empty");
    q->front = (q->front+1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

element peek(QueueType *q){
    if (is_empty(q)) error("q is empty");
    return q->queue[q->front];
}

double q_random(){
    // 0 <= rand() <= maximum integer(=rand_max)
    // rand()함수가 낼 수 있는 최대값(RAND_MAX)로 나누었으므로
    // 0 <= return value <= 1이 된다
    return rand() / (double) RAND_MAX;
}

// variables for simulation : 시뮬레이션용 변수들
int duration = 10; // simulation time : 총 시뮬레이션 시간
double arrival_prob = 0.7; // probability of customer arrival : 고객 도착 확률
int max_serv_time = 5; // max service time per a customer : 최대 서비스 시간
int q_clock; // current simulation time

// result variables
int customers; // number of all customers
int served_customers; // number of serviced customers
int waited_time; // waiting time of all of customers

// 0.7의 확률로 고객 생산
int is_customer_arrived(){
    if (q_random() < arrival_prob) {
        return TRUE;
    }
    return FALSE;
}

void insert_customer(int arrival_time){
    element customer;
    customer.id = customers++;
    customer.arrival_time = arrival_time;
    // 서비스 시간 = 1,2,3,4,5 중에 하나가 선택된다
    customer.service_time = (int)(max_serv_time * q_random()) + 1;
    enqueue(&q, customer);
    printf("고객번호 [%d]이 %d분에 도착했습니다. 서비스 시간은 %d분입니다.\n",
           customer.id,
           customer.arrival_time,
           customer.service_time);
}

// 대기 중인 고객을 한명 꺼내서 서비스를 실행한다
int remove_customer(){
    element customer;
    int service_time;
    
    if (is_empty(&q)) return 0; // 기다리는 고객이 없다
    customer = dequeue(&q);
    printf("%d %d %d %d\n", q_clock, customer.id, customer.arrival_time, customer.service_time);
    
    service_time = customer.service_time - 1; // ?
    served_customers++;
    printf("%d\n", service_time);

    
    waited_time += q_clock - customer.arrival_time; // 현재시간 - 도착시간
    printf("%d\n", waited_time);

    printf("고객번호 [%d]이 %d분에 서비스를 시작합니다. 대기시간은 %d분이었습니다.\n",
           customer.id, q_clock, q_clock-customer.arrival_time);
    
    return service_time;
}

void print_stat(){
    printf("서비스 받은 고객 수 = %d\n",served_customers);
    printf("전체 대기 시간 = %d분",waited_time);
    printf("1인당 평균 대기 시간 = %f분\n",(double)waited_time/served_customers);
    printf("서비스를 받지 못하고 대기 중인 고객 수 = %d\n",customers-served_customers);
}

int main(){
    int service_time = 0;
    int service_time2 = 0;
    q_clock = 0;
    
    while (q_clock < duration) {
        q_clock++;
        printf("현재 시각=%d\n",q_clock);
        if (is_customer_arrived())
            insert_customer(q_clock);
        if (service_time > 0) // server가 하나임을 의미한다
            service_time--;   // 한명의 고객이 모두 처리될 때까지 다른 고객을 받지 않는다
        else
            service_time = remove_customer();
        if (service_time2 >0)
            service_time2--;
        else
            service_time2 = remove_customer();
    }
    
    print_stat();
    return 0;
}
#endif
