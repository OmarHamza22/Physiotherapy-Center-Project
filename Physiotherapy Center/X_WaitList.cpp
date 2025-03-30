#include "X_WaitList.h"

void X_WaitList::CancelAppointment(int patientID) {
    LinkedQueue<Patient*> tempQueue;
    Patient* tempPatient = nullptr;
    
    while (!isEmpty()) {
        dequeue(tempPatient);
        if (tempPatient->getID() != patientID) {
            tempQueue.enqueue(tempPatient);
        } else {
            delete tempPatient;
        }
    }
    
    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(tempPatient);
        enqueue(tempPatient);
    }
}
