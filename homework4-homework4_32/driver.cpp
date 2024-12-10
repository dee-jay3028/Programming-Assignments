#include <iostream>
#include <fstream>
#include "arrayQueue.h"
#include "priorityQueue.h"
#include "event.h"

using namespace std;

void testPriority();

int main() {
    ArrayQueue<int> arrivalTimes;
    ArrayQueue<int> transactionTimes;

    ifstream inputFile("input.txt");
    ArrayQueue<int> myQueue;

    if (!inputFile.is_open()) {
        cout << "Unable to open file." << endl;
        return 1;
    }
    int totalCustomers = 0;
    int totalWaitingTime = 0;

    int arrivalTime, transactionTime;
    while (inputFile >> arrivalTime >> transactionTime) {
        arrivalTimes.enqueue(arrivalTime);
        transactionTimes.enqueue(transactionTime);
    }
    inputFile.close();

    int currentTime = 0;

    while (!arrivalTimes.isEmpty()) {
        
        int arrivalTime = arrivalTimes.peekFront();
        int transactionTime = transactionTimes.peekFront();

        // if (currentTime >= arrivalTime) {
        //     totalCustomers++;
        //     totalWaitingTime += currentTime - arrivalTime;
        //     arrivalTimes.dequeue();
        //     transactionTimes.dequeue();
        //     currentTime += transactionTime;
        // } else {
           
        //     currentTime = arrivalTime;
        if (currentTime >= arrivalTime) {
            totalCustomers++;

            int waitTime = currentTime - arrivalTime;
            totalWaitingTime += waitTime;
            cout << "Customer arrived at time " << arrivalTime << ", and he has to wait " << waitTime <<" minutes"<< endl;
            arrivalTimes.dequeue();
            transactionTimes.dequeue();
            currentTime += transactionTime;
        } else {
            currentTime = arrivalTime;
        }
    }

    double averageWaitingTime;
    if (totalCustomers > 0) {
        averageWaitingTime = (1.0 * totalWaitingTime) / totalCustomers;
    } else {
        averageWaitingTime = 0;
    }

    cout << "Total number of arrivals: " << totalCustomers << endl;
    cout << "Average time spent waiting in line: " << averageWaitingTime << endl;

    testPriority();

    return 0;
}

void testPriority(){
    PriorityQueue<Event> myPriority;
    Event event1(1, 20, "customer 1 arrives");
    Event event2(5, 10, "customer 2 arrives");
    Event event3(21, 0, "customer 1 departs");
    Event event4(31, 0, "customer 2 departs");
    myPriority.enqueue(event1);
    myPriority.enqueue(event2);
    myPriority.enqueue(event3);
    myPriority.enqueue(event4);
    cout<<"TOP: "<<myPriority.peekFront().getType()<<endl;
    myPriority.dequeue();
    cout<<"DEQUEUED"<<endl;
    cout<<"TOP: "<<myPriority.peekFront().getType()<<endl;
    myPriority.dequeue();
    cout<<"DEQUEUED"<<endl;
    cout<<"TOP: "<<myPriority.peekFront().getType()<<endl;
    myPriority.dequeue();
    cout<<"DEQUEUED"<<endl;
    cout<<"TOP: "<<myPriority.peekFront().getType()<<endl;
    myPriority.dequeue();
    cout<<"DEQUEUED"<<endl;    
    cout<<"EMPTY: "<<myPriority.isEmpty()<<endl;
}
