
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//Function Prototypes:
static int stringToInt(string s);
static string intToString( int i );
static void insertIncomingPatients( Patient * patients, int numOfPatients,
                                    PriorityQueue & waitingList, int time );
static bool doctorAvailable( Doctor * doctors, int doctorAmt, int & availableDoctorNo );
static double simulate( int numOfPatients, Patient * patientsInOrderOfArrival, PriorityQueue waitingList,
                        int doctorAmt, int maxTime, string & out );
static double simulateUntilMinAvgTime( maxHeap1 h, PriorityQueue waitingList, int maxAvgWaitingTime, int maxTime );
static int getMaxTime( Patient * patients, int patientAmt );


int main(int argc, char *argv[]) {


    if(argc != 3) {
        cout << "Enter input file and maximum avg. waiting time as arguments." << endl;
        return 0;
    }


    //Simulate for maxHeap1
    string inputFile;
    int maxAvgWaitingTime;

    inputFile = argv[1];
    maxAvgWaitingTime = stringToInt(argv[2] );

    maxHeap1 h( maxAvgWaitingTime );
    h.initPatients( inputFile );
    int maxTime = getMaxTime( h.getPatientsInOrderOfArrival(), h.getNumOfPatients() );
    PriorityQueue waitingList;
    simulateUntilMinAvgTime(h, waitingList, maxAvgWaitingTime, maxTime );

    waitingList.deleteHeap();
    h.delDynamicPatients();
    return 0;

 }


 /*
  * Calculate approximately maximum possible time for the simulation to finish.
  */
 static int getMaxTime( Patient * patients, int patientAmt ) {

    int maxTime = 0;
    for( int i = 0; i < patientAmt; i++ ) { //find maximum service time
        maxTime += patients[i].getServiceTime();
    }

    return maxTime;
}

static int stringToInt(string s) {

    stringstream convert(s);
    int number = 0;
    convert >> number;
    return number;
}

static string intToString( int i ) {
    stringstream convert;
    convert << i;
    return convert.str();
}

/*
 * Insert the patients whose arrivalTime is equal to the current time.
 */
static void insertIncomingPatients( Patient * patients, int numOfPatients,
                                    PriorityQueue & waitingList, int time ) {

    for( int i = 0; i < numOfPatients; i++ ) {

        if( time == patients[i].getArrivalTime() ) {
            waitingList.pqInsert(patients[i]);
        }

    }


}

/*
 * Returns true if one of the doctors are available and the doctor no of the available doctor.
 */
static bool doctorAvailable( Doctor * doctors, int doctorAmt, int & availableDoctorNo ) {

    for( int i = 0; i < doctorAmt; i++ ) {

        if( doctors[i].getAvailable() ) { //There is an available doctor
            availableDoctorNo = i;
            return true;
        }

    }

    return false;

}

static double simulate( int numOfPatients, Patient * patientsInOrderOfArrival, PriorityQueue waitingList,
                        int doctorAmt, int maxTime, string & out ) {

    Doctor doctors[doctorAmt];
    double totalWaitingTime = 0;

    for( int currTime = 0; currTime < maxTime; currTime++ ) {

        //update doctors remaining time to become available again
        for( int i = 0; i < doctorAmt; i++ ) {

            if( !doctors[i].getAvailable() ) { //if the doctor is not available
                doctors[i].reduceRemainingTime();
            }

        }


        //insert incoming patients into the waiting list
        insertIncomingPatients(patientsInOrderOfArrival, numOfPatients, waitingList, currTime );

        //if a doctor is available, make appointments based on the priority queue (waitingList)
        int availableDoctorNo;
        while( !waitingList.pqIsEmpty() && doctorAvailable( doctors, doctorAmt, availableDoctorNo ) ) {

            Patient p;
            waitingList.pqDelete( (PQItemType &)(p) );
            int waitTime = currTime - p.getArrivalTime();
            totalWaitingTime += waitTime;

            out = out + "Doctor " + intToString(availableDoctorNo) + " takes patient " +
                  intToString( p.getId() ) + " at minute " + intToString( currTime ) +
                  " (wait: " + intToString (waitTime ) + " mins)\n";

            doctors[availableDoctorNo].setNonAvailable(); //make doctor unavailable
            doctors[availableDoctorNo].setRemainingTime(p.getServiceTime()); //set the unavailable time of doctor
        }

    }

    return (double)totalWaitingTime / numOfPatients;

}

/*
 * Call simulate function until the condition (avg <= maxAvgWaitingTime) fits.
 */
static double simulateUntilMinAvgTime( maxHeap1 h, PriorityQueue waitingList, int maxAvgWaitingTime, int maxTime ) {

    int doctorAmt = 1;
    string out = "";

    while(true) {
        out = "";
        double avg = simulate( h.getNumOfPatients(), h.getPatientsInOrderOfArrival(),
                               waitingList, doctorAmt, maxTime, out );

        if( avg <= maxAvgWaitingTime ) {
            cout << "\nMinimum number of doctors required: " + intToString(doctorAmt) + "\n";
            cout << endl << "Simulation with " << doctorAmt << " doctors:\n\n";
            cout << out << endl;
            cout << "Average waiting time: " << avg << " minutes" << endl;
            return avg;
        }

        doctorAmt++;
    }

}
