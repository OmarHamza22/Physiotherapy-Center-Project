#include "X_WaitList.h"

void X_WaitList::CancelAppointment(int patientID, ArrayStack<Patient*>& finishedPatients) {
    LinkedQueue<Patient*> tempQueue;
    Patient* tempPatient = nullptr;

    while (!isEmpty()) {
        dequeue(tempPatient);
        if (tempPatient->getID() != patientID) {
            tempQueue.enqueue(tempPatient);
        }
        else {
            finishedPatients.push(tempPatient); // Push to finished stack
        }
    }

    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(tempPatient);
        enqueue(tempPatient);
    }
}

void X_WaitList::randCancelAppointment(int Peancel, ArrayStack<Patient*>& finishedPatients) {
    LinkedQueue<Patient*> tempQueue;
    Patient* tempPatient = nullptr;
    Patient* eligiblePatients[100];
    int eligibleCount = 0;

    while (!isEmpty()) {
        dequeue(tempPatient);

        if (tempPatient->getRequiredTreatmentsNum() == 1) {
            eligiblePatients[eligibleCount] = tempPatient;
            eligibleCount++;
        }

        tempQueue.enqueue(tempPatient);
    }

    if (eligibleCount > 0) {
        int randomIndex = rand() % eligibleCount;
        Patient* selectedPatient = eligiblePatients[randomIndex];

        CancelAppointment(selectedPatient->getID(), finishedPatients); 
    }

    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(tempPatient);
        enqueue(tempPatient);
    }
}
