#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class PriorityQueue {
private:
    vector<T> heap;  // Min-heap storage

    // Helper function to maintain heap property
    void heapifyUp(int index) {
        int parent = (index - 1) / 2;
        while (index > 0 && heap[index] < heap[parent]) {
            swap(heap[index], heap[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    // Helper function to maintain heap property
    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < heap.size() && heap[leftChild] < heap[smallest])
            smallest = leftChild;

        if (rightChild < heap.size() && heap[rightChild] < heap[smallest])
            smallest = rightChild;

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    // Insert an element into the priority queue
    void push(const T& item) {
        heap.push_back(item);
        heapifyUp(heap.size() - 1);
    }

    // Remove and return the highest priority element
    T pop() {
        if (heap.empty()) {
            throw runtime_error("Priority Queue is empty!");
        }
        T topItem = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return topItem;
    }

    // Return the highest priority element without removing it
    T top() const {
        if (heap.empty()) {
            throw runtime_error("Priority Queue is empty!");
        }
        return heap[0];
    }

    // Check if the queue is empty
    bool empty() const {
        return heap.empty();
    }

    // Get size of the queue
    int size() const {
        return heap.size();
    }
};
#endif
