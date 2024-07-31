#pragma once
#include "libraries.h"

template<typename T>
class Queue {
private:
    struct StudentNode {
        T data;
        StudentNode* next;

        StudentNode(T val) : data(val), next(nullptr) {}
    };

    StudentNode* front;
    StudentNode* rear;
    int size;
public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(T value) {
        StudentNode* newNode = new StudentNode(value);
        if (rear == nullptr) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    void dequeue() {
        if (isEmpty()) {
            std::cout << "Queue is empty" << std::endl;
            return;
        }
        StudentNode* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        size--;
    }

    T getFront() const {
        if (isEmpty()) {
            std::cout << "Queue is empty" << std::endl;
            return 0;
        }
        return front->data;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    int getSize() const {
        return size;
    }

};
