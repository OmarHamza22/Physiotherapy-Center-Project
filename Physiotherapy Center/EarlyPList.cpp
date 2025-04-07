#include "EarlyPList.h"

EarlyPList::EarlyPList() : priQueue<Patient*>() {
    
}
    
bool EarlyPList::reschedule(Patient* p, int newPT) {
    priQueue<Patient*> tempQueue;
    Patient* current;
    int priority;
    bool found = false;

    if (newPT < p->getappointmentTime())
    {
        /// maybe we add a message ??
        return false;
    }
    

    while (!this->isEmpty()) {
        if (this->dequeue(current, priority)) {
            if (current == p) {
                current->setappointmentTime(newPT);  // Update pt
                found = true;
                return found;
            }
            // queue with updated priority
            tempQueue.enqueue(current, current->getappointmentTime());
        }
    }

    // Restore the queue
    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(current, priority);
        this->enqueue(current, priority);
    }

    
    if (!found)
    {
        // maybe we add a message ??
        return false;
    }
}


bool EarlyPList::randReschedule(int Presc) {
    // Random number generation for deciding whether to reschedule
    int roll = rand() % 101;

    // Step 1: If the random roll is greater than or equal to Presc, no reschedule occurs
    if (roll >= Presc || this->isEmpty()) {
        return false;
    }

    // Step 2: Get the size of the queue using the priQueue's size member variable
    int numPatients = this->getSize(); // Use the size member variable directly from the priQueue class

    // If no patients exist, return false
    if (numPatients == 0) {
        return false;
    }

    // Step 3: Pick a random index to select a patient
    int index = rand() % numPatients;
    Patient* selected = nullptr;
    int priority;

    // Step 4: Dequeue patients until we reach the selected index
    priQueue<Patient*> tempQueue;
    for (int i = 0; i < numPatients; i++) {
        Patient* current;
        this->dequeue(current, priority); // Dequeue from the main queue

        if (i == index) {
            selected = current;
        }

        // Re-enqueue the patient into tempQueue
        tempQueue.enqueue(current, priority);
    }

    // Step 5: Generate a new appointment time (must be greater than the old one)
    int oldPT = selected->getappointmentTime();
    int newPT = oldPT + (rand() % 10 + 1); // Adjust the range if necessary

    // Step 6: Call the reschedule function with the selected patient and the new time
    bool rescheduled = this->reschedule(selected, newPT);

    // Restore the original queue from tempQueue
    while (!tempQueue.isEmpty()) {
        Patient* current;
        int priority;
        tempQueue.dequeue(current, priority);
        this->enqueue(current, priority);
    }

    // Return whether the reschedule was successful
    return rescheduled;
}


