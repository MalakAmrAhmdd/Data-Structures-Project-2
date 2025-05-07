#include <bits/stdc++.h>
using namespace std;

struct Patient {
    string name;
    int severity;
    int arrival_time;
};

class MaxHeap {
private:
    Patient heap[100];
    int size;

    void heapify_up(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (compare(heap[parent], heap[index])) {
                swap(heap[parent], heap[index]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapify_down(int index) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size && compare(heap[largest], heap[left])) {
                largest = left;
            }
            if (right < size && compare(heap[largest], heap[right])) {
                largest = right;
            }
            if (largest == index) break;

            swap(heap[index], heap[largest]);
            index = largest;
        }
    }

    bool compare(const Patient &a, const Patient &b) {
        if (a.severity == b.severity) {
            return a.arrival_time > b.arrival_time;
        }
        return a.severity < b.severity;
    }

public:
    MaxHeap() : size(0) {}

    void insert(const Patient &patient) {
        if (size >= 100) {
            cerr << "Heap is full!" << endl;
            return;
        }
        heap[size] = patient;
        heapify_up(size);
        size++;
    }

    Patient extract_max() {
        if (size == 0) {
            return {"", -1, -1};
        }
        Patient max_patient = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapify_down(0);
        return max_patient;
    }

    Patient peek() const {
        if (size == 0) {
            return {"", -1, -1};
        }
        return heap[0];
    }

    void print_heap() const {
        for (int i = 0; i < size; i++) {
            cout << heap[i].name << " ";
        }
        cout << endl;
    }
};

int main() {
    ifstream inFile("Problem 4.txt");
    if (!inFile) {
        cerr << "Cannot open file.\n";
        return 1;
    }

    MaxHeap emergencyRoom;
    Patient patients[100];
    int count = 0;
    while (inFile >> patients[count].name >> patients[count].severity >> patients[count].arrival_time) {
        count++;
    }

    for (int i = 0; i < count; i++) {
        cout << "Inserting: " << patients[i].name << endl;
        emergencyRoom.insert(patients[i]);
        cout << "Heap: ";
        emergencyRoom.print_heap();
    }

    cout << "Treatment Order:" << endl;
    while (true) {
        Patient treated = emergencyRoom.extract_max();
        if (treated.severity == -1) break;
        cout << "Treating: " << treated.name << endl;
    }

    return 0;
}