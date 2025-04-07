#include "X_WaitList.h"

void X_WaitList::CancelAppointment(int patientID) {
    LinkedQueue<Patient*> tempQueue;
    Patient* tempPatient = nullptr;
    
    while (!isEmpty()) {
        dequeue(tempPatient);
        if (tempPatient->getID() != patientID) {
            tempQueue.enqueue(tempPatient);
        } else {
            //push finished stack
            delete tempPatient;
        }
    }
    
    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(tempPatient);
        enqueue(tempPatient);
    }
}

void X_WaitList::randCancelAppointment(int Peancel) {
    LinkedQueue<Patient*> tempQueue;
    Patient* tempPatient = nullptr;
    Patient* eligiblePatients[100]; // Array to hold eligible patients (size can be adjusted)
    int eligibleCount = 0;  // To count how many patients are eligible

    // Step 1: Iterate through the waiting list and find eligible patients
    while (!isEmpty()) {
        dequeue(tempPatient);

        // Check if the patient can cancel (is their last treatment)
        if (tempPatient->getRequiredTreatmentsNum() == 1) {  // If the patient has only 1 treatment left
            // Store the eligible patient in the array
            eligiblePatients[eligibleCount] = tempPatient;
            eligibleCount++;
        }

        // Add patient back to tempQueue
        tempQueue.enqueue(tempPatient);
    }

    // Step 2: If there are eligible patients, randomly select one to cancel
    if (eligibleCount > 0) {
        // Pick a random patient index from the array of eligible patients
        int randomIndex = rand() % eligibleCount;
        Patient* selectedPatient = eligiblePatients[randomIndex];

        // Step 3: Call the original CancelAppointment with the selected patient ID
        CancelAppointment(selectedPatient->getID());
    }

    // Step 4: Restore the original queue from tempQueue
    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(tempPatient);
        enqueue(tempPatient);
    }
}