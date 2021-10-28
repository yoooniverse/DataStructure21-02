//
//  main.c
//  DS_assignment04-02_1720047
//  Assignment4-2
//  작성자 : 국어국문학과 1720047 이윤경
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#define MAX_QUEUE_SIZE    100
#define FALSE 0
#define TRUE 1

typedef struct element {
    int id;
    int arrival_time; //고객 도착 시간
    int service_time; // 고객이 받는 서비스 시간
} element;         // Customer structure

typedef struct QueueType {
    element  queue[MAX_QUEUE_SIZE];
    int  front, rear;
} QueueType;

QueueType queue; //전역변수로 설정함

// Real random number generation function between 0 and 1
// 0 <= rand() <= maximum integer(=rand_max)
double q_random(void) {
    return rand() / (double)RAND_MAX; //rand()함수가 낼 수 있는 최대값(RAND_MAX)로 나누었으므로 0과 1사이의 값이 나온다
}

// Various state variables needed for simulation : 시뮬레이션용 변수들
int duration = 10; // Simulation time : 총 시뮬레이션 시간
double arrival_prob = 0.7; // Average number of customers arriving in one time unit : 고객 도착 확률
int max_serv_time = 9; // maximum service time for one customer : 최대 서비스 시간
int q_clock; // current simulation time

// Results of the simulation
int customers; // Total number of customers
int served_customers; // Number of customers served
int waited_time; // Time the customers waited

// Empty state detection function
int is_empty(QueueType * q){
    return (q->front == q->rear);
}
// Full state detection function
int is_full(QueueType * q){
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// Insert function
void enqueue(QueueType * q, element item){
    if (is_full(q)) printf("Queue is full\n");
    q->rear = (q->rear+1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}
// delete function
element dequeue(QueueType *q){
    if (is_empty(q)) printf("Queue is empty\n");
    q->front = (q->front+1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

// Generate a random number.
// If it is smaller than 'arrival_prob', assume that new customer comes in the bank.
int is_customer_arrived(void){
    if (q_random() <arrival_prob) return TRUE;
    else return FALSE;
}
// Insert newly arrived customer into queue
void insert_customer(int arrival_time){
    element customer;

    customer.id = customers++;
    customer.arrival_time = arrival_time;
    customer.service_time = (int)(max_serv_time * q_random()) + 1;
    
    enqueue(&queue, customer);

    printf("Customer [%d] comes in %d minutes. Service time is %d minutes.\n", customer.id, customer.arrival_time, customer.service_time);
}

// Retrieve the customer waiting in the queue and return the customer's service time.
int remove_customer(char counter)
{
    element customer;
    int service_time;

    if (is_empty(&queue)) return 0;
    customer = dequeue(&queue);
    printf("%d %d %d %d\n", q_clock, customer.id, customer.arrival_time, customer.service_time);
    service_time = customer.service_time - 1;
    printf("%d\n", service_time);
    served_customers++;
    
    waited_time += (q_clock - customer.arrival_time);
    printf("%d", waited_time);
    printf("At counter %c : Customer %d starts service in %d minutes. Wait time was %d minutes.\n", counter, customer.id, q_clock, q_clock - customer.arrival_time);
    
    return service_time;
}


// Print the statistics.
void print_stat(void)
{
    printf("=======result=======\n");
    printf("Number of customers served = %d\n", served_customers);
    printf("Total wait time = %d minutes\n", waited_time);
    printf("Average wait time per person = %f minutes\n", (double)waited_time / served_customers);
    printf("Number of customers still waiting = %d\n", customers - served_customers);
}


// Simulation program
int main(void)
{
    int A_service_time = 0;
    int B_service_time = 0;
    q_clock = 0;
    
    while (q_clock < duration) {
        q_clock++;
        printf("Current time=%d\n", q_clock);
        
        if (is_customer_arrived()) insert_customer(q_clock);

        // Check if the customer who is receiving the service is finished.// the customer is receiving service
        if (A_service_time > 0) A_service_time--;
        else                    A_service_time = remove_customer('A');
        // no customer is receiving service.
        // So, take out a customer from the queue and start the service.
        
        
        if (B_service_time > 0) B_service_time--;
        else                    B_service_time = remove_customer('B');
        
        printf("\n");
    }
    print_stat();
    
    return 0;
}
