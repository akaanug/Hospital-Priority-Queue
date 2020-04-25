
#include "maxHeap2.h"
#include <fstream>
#include <sstream>

using namespace std;

// Default constructor
Heap::Heap() : size(0) {
    currentSize = 10;
    items = new HeapItemType[currentSize];
}


bool Heap::heapIsEmpty() const {
    return (size == 0);
}

void Heap::heapInsert(const HeapItemType & newItem) {

    // Place the new item at the end of the heap
    items[size] = newItem;

    // Trickle new item up to its proper position
    int place = size;
    int parent = (place - 1)/2;
    while ( (place > 0) && (items[place].getKey() > items[parent].getKey()) ) {
        HeapItemType temp = items[parent];
        items[parent] = items[place];
        items[place] = temp;

        place = parent;
        parent = (place - 1)/2;
    }
    ++size;

    if(size == currentSize) {
        currentSize = currentSize * 2;
        //deep copy into temp
        HeapItemType * temp = new HeapItemType[currentSize];
        for( int i = 0; i < size; i++ ) {
            temp[i] = items[i];
        }

        delete [] items;
        items = temp;
    }


}



void Heap::heapDelete(HeapItemType & rootItem) throw(HeapException) {
    if (heapIsEmpty())
        throw HeapException("HeapException: Heap empty");
    else {

        rootItem = items[0];
        items[0] = items[--size];
        heapRebuild(0);

        if( (currentSize > 10) && (size <= currentSize / 2) ) { //min array size is 10
            currentSize = currentSize / 2;

            //Halve the array
            HeapItemType * temp = new HeapItemType[currentSize];
            for( int i = 0; i < size; i++ ) {
                temp[i] = items[i];
            }

            delete [] items;
            items = temp;

        }

    }
}

void Heap::heapRebuild(int root) {
    int child = 2 * root + 1;    // index of root's left child, if any
    if (child < size) {
        // root is not a leaf so that it has a left child
        int rightChild = child + 1;    // index of a right child, if any
        // If root has right child, find larger child
        if ((rightChild < size) &&
            (items[rightChild].getKey() > items[child].getKey()))
            child = rightChild;    // index of larger child

        // If root’s item is smaller than larger child, swap values
        if (items[root].getKey() < items[child].getKey()) {
            HeapItemType temp = items[root];
            items[root] = items[child];
            items[child] = temp;

            // transform the new subtree into a heap
            heapRebuild(child);
        }
    }
}

bool PriorityQueue::pqIsEmpty() const {
    return h.heapIsEmpty();
}

void PriorityQueue::pqInsert(const PQItemType& newItem) throw (PQException){
    try {
        h.heapInsert(newItem);
    }
    catch (HeapException e) {
        throw PQException("Priority queue is full");
    }
}

void PriorityQueue::pqDelete(PQItemType& priorityItem) throw (PQException) {
    try {
        h.heapDelete(priorityItem);
    }
    catch (HeapException e) {
        throw PQException("Priority queue is empty");
    }
}

void extractInts( string s, int arr[] ) {

    stringstream ss;
    ss << s;
    string curr;
    int res;
    int count = 0;

    while(!ss.eof()) {

        ss >> curr;

        if( stringstream(curr) >> res ) {
            arr[count] = res;
            count++;
        }

        curr = " ";
    }

}


void maxHeap1::initPatients(string file) {
    ifstream inFile;
    inFile.open(file.c_str());

    string line;
    int line_count = 0;

    // Loop to get each line in file
    while(getline(inFile, line)) {
        stringstream ss(line);
        string value;
        int data[4];
        getline(ss, value );

        extractInts(value, data);
        if(line_count != 0) {
            if(patientsInOrderOfArrival != NULL ) {
                patientsInOrderOfArrival[line_count-1] = Patient(data[0], data[1],
                                                             data[2], data[3]);
            }
        } else {
            numOfPatients = data[0];
            patientsInOrderOfArrival = new Patient[numOfPatients];
        }

        line_count++;

    }

}
