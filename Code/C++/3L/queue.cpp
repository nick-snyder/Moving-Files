/**
 * CS515 Lab 3
 * File: queue.cpp
 * Name: Nick Snyder
 * Section: 2
 * Date: 20 February 2022
 * Collaboration Declaration: online resources
 */

#include "queue.h"

// circular array implementation of queue
queue::queue(){
    rear = -1;  // rear used as the count of queue items
    front = 0;  // front points to queue front
	for(int i=0; i<MAX_CAP; i++)
		item[i]=0;   
}

void queue::enqueue(int data){
    if (!full()) {
        rear = (rear + 1) % MAX_CAP;
        item[rear] = data;
    }
}

int queue::dequeue(){
    if (empty()) {
        return 0;
    } else if (front == rear) {
        int temp = item[front];
        rear = -1;
        front = 0;
        return temp;
    } else {
        int temp = item[front];
        front = (front + 1) % MAX_CAP;
        return temp;
    }
}

void queue::dump(ostream &os){
    for(int i=front; i<=rear; i++) {
        os<<item[i]<<endl;
        //os<<printf("%d\n", item[i]);
    }
}

int queue::size(){
    if (rear == -1) {
        return 0;
    } else {
        if (front > rear) {
            return (MAX_CAP - front + rear + 1);
        } else {
            return (rear - front + 1);
        }
    }
}

bool queue::empty(){
    return size() == 0;
}

bool queue::full(){
    return (size() >= MAX_CAP) ? true : false;   
}