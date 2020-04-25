
#ifndef C202_HW3_MAXHEAP1_H
#define C202_HW3_MAXHEAP1_H

#include <exception>
#include <string>

using namespace std;

// -------------------------------------------Patient Class-------------------------------------------------------------

class Patient {

public:
    Patient() { }

    Patient( int patientId, int priority, int arrivalTime, int serviceTime ) {
        this->patientID = patientId;
        this->priority = priority;
        this->arrivalTime = arrivalTime;
        this->serviceTime = serviceTime;
    }

    int getId() {
        return patientID;
    }

    int getPriority() {
        return priority;
    }

    int getArrivalTime() {
        return arrivalTime;
    }

    int getServiceTime() {
        return serviceTime;
    }

private:
    int patientID;
    int priority;
    int arrivalTime;
    int serviceTime;

};

// -------------------------------------------End of Patient Class------------------------------------------------------




// -------------------------------------------KeyedItem Class-----------------------------------------------------------
typedef int KeyType;
class KeyedItem {
public:
    KeyedItem() { }
    KeyedItem(Patient p) : patientID( p.getId() ), priority( p.getPriority() ),
    arrivalTime( p.getArrivalTime() ), serviceTime( p.getServiceTime() ) { }

    KeyType getKey() const {
        return priority;
    }

    KeyType getPatientId() const {
        return patientID;
    }

    KeyType getPriority() const {
        return priority;
    }

    KeyType getArrivalTime() const {
        return arrivalTime;
    }

    KeyType getServiceTime() const {
        return serviceTime;
    }

private:
    KeyType patientID;
    KeyType priority;
    KeyType arrivalTime;
    KeyType serviceTime;
};
//-------------------------------------------End of KeyedItem Class-----------------------------------------------------




// -------------------------------------------HeapException Class-------------------------------------------------------
class HeapException : public exception{

private:
    string msg;

public:
    virtual const char* what() const throw()
    {
        return msg.c_str();
    }
    HeapException(const string & message =""):
            exception(), msg(message) {};
    ~HeapException() throw() {};

}; // end HeapException
// ------------------------------------End of HeapException Class-------------------------------------------------------




// -------------------------------------------PQException Class---------------------------------------------------------
class PQException : public exception{

private:
    string msg;

public:
    virtual const char* what() const throw()
    {
        return msg.c_str();
    }
    PQException(const string & message =""):
            exception(), msg(message) {};
    ~PQException() throw() {};

}; // end HeapException
// ------------------------------------End of PQException Class---------------------------------------------------------





//-------------------------------------------Heap Class-----------------------------------------------------------------
const int MAX_HEAP = 2000;
typedef KeyedItem HeapItemType;

class Heap {
public:
    Heap();				// default constructor
    // copy constructor and destructor are supplied by the compiler

    bool heapIsEmpty() const;
    void heapInsert(const HeapItemType& newItem) throw(HeapException);
    void heapDelete(HeapItemType& rootItem) throw(HeapException);

protected:
    void heapRebuild(int root);		// Converts the semiheap rooted at
    // index root into a heap
private:
    HeapItemType items[MAX_HEAP];	// array of heap items
    int          size;            	// number of heap items
};
//---------------------------------------------End of Heap Class--------------------------------------------------------




//-------------------------------------------PriorityQueue Class--------------------------------------------------------
typedef HeapItemType PQItemType;

class PriorityQueue {
public:
    // default constructor, copy constructor, and destructor
    // are supplied by the compiler

    // priority-queue operations:
    bool pqIsEmpty() const;
    void pqInsert(const PQItemType& newItem) throw (PQException);
    void pqDelete(PQItemType& priorityItem) throw (PQException);
    void deleteHeap() { }

        private:
    Heap h;
};

//-----------------------------------End of PriorityQueue Class---------------------------------------------------------



//---------------------------------------------Doctor Class-------------------------------------------------------------
class Doctor {
public:
    Doctor( ){ available = true; }

    void setAvailable() {
        available = true;
    }

    void setNonAvailable() {
        available = false;
    }

    bool getAvailable() {
        return available;
    }

    void setRemainingTime( int time ) {
        remainingTime = time;
    }

    void reduceRemainingTime( ) {
        remainingTime = remainingTime - 1;
        if(remainingTime == 0) {
            setAvailable();
        }
    }

private:
    bool available;
    int remainingTime;
};
//------------------------------------End of Doctor Class---------------------------------------------------------------



//----------------------------------------maxHeap1 Class----------------------------------------------------------------

class maxHeap1 {
public:
    maxHeap1( int maxAvgWaitingTime ) : maxAvgWaitingTime( maxAvgWaitingTime ) { }
    void initPatients( string file );
    int getNumOfPatients() { return numOfPatients; }
    Patient * getPatientsInOrderOfArrival() { return patientsInOrderOfArrival; }
    void delDynamicPatients() { }

private:
    int numOfPatients;
    int maxAvgWaitingTime;
    Patient patientsInOrderOfArrival[MAX_HEAP];
};

#endif //C202_HW3_MAXHEAP1_H

//-------------------------------------End of maxHeap1 Class------------------------------------------------------------