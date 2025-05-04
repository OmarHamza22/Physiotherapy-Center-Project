#include "X_WaitList.h"

void X_WaitList::CancelAppointment(Patient* targetPatient, ArrayStack<Patient*>& finishedPatients, int timestep) {
    if (!targetPatient) return;

    LinkedQueue<Patient*> tempQueue;
    Patient* tempPatient = nullptr;

    while (!this->isEmpty()) {
        dequeue(tempPatient);
        if (tempPatient->getID() == targetPatient->getID()) {
            tempPatient->setCancelStatus(true);
            tempPatient->setfinishTime(timestep);
            finishedPatients.push(tempPatient);  // Safely push to finished stack
        }
        else {
            tempQueue.enqueue(tempPatient);  // Keep others
        }
    }

    // Restore queue
    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(tempPatient);
        enqueue(tempPatient);
    }
}


void X_WaitList::randCancelAppointment(int Pcancel, ArrayStack<Patient*>& finishedPatients, int timestep) {
    // 1 -rand 
    int roll = rand() % 101; // Generates [0, 100]
    if (roll >= Pcancel) return;  // No cancellation this timestep

    // 2 - find patient
    LinkedQueue<Patient*> tempQueue;
    Patient* tempPatient = nullptr;
    Patient* eligiblePatients[100];  // Static array, no STL
    int eligibleCount = 0;

    while (!isEmpty()) {
        dequeue(tempPatient);
        if (tempPatient->getRequiredTreatmentsNum() == 1) {
            // Only consider patients with one remaining treatment
            eligiblePatients[eligibleCount++] = tempPatient;
        }
        tempQueue.enqueue(tempPatient); // Keep all in a temporary queue
    }

    // 3 put it back
    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(tempPatient);
        enqueue(tempPatient);
    }

    // 4 - break if no suitable
    if (eligibleCount == 0) return;

    // 5 - get rand patient
    int randomIndex = rand() % eligibleCount;
    int targetID = eligiblePatients[randomIndex]->getID();

    // 6 - remove patient from Q
    LinkedQueue<Patient*> finalQueue;
    while (!isEmpty()) {
        dequeue(tempPatient);
        if (tempPatient->getID() == targetID) {
            tempPatient->setCancelStatus(true);
            tempPatient->setfinishTime(timestep);
            finishedPatients.push(tempPatient); 
        }
        else {
            finalQueue.enqueue(tempPatient);
        }
    }

    // put patients back
    while (!finalQueue.isEmpty()) {
        finalQueue.dequeue(tempPatient);
        enqueue(tempPatient);
    }
}



