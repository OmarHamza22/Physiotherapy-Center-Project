#include "EarlyPList.h"

EarlyPList::EarlyPList() : priQueue<Patient*>() {
    
}
    
bool EarlyPList::reschedule(Patient* p, int newPT) {
    priQueue<Patient*> tempQueue;
    Patient* current = nullptr;
    int priority = 0;
    bool found = false;

    if (newPT < p->getappointmentTime()) {
        return false; // Can't reschedule to an earlier time
    }

    while (!this->isEmpty()) {
        this->dequeue(current, priority);
        if (current == p) {
            current->setappointmentTime(newPT);  // Update appointment time
            found = true;
            // Enqueue later with updated priority
        }
        else {
            tempQueue.enqueue(current, current->getappointmentTime());
        }
    }

    // Reinsert the updated patient with new priority
    if (found) {
        tempQueue.enqueue(p, -newPT);
    }

    // Restore original queue
    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(current, priority);
        this->enqueue(current, priority);
    }

    return found;
}



bool EarlyPList::randReschedule(int Presc) {
    int roll = rand() % 101;

    // If the roll fails or the queue is empty, no rescheduling happens
    if (roll >= Presc || this->isEmpty()) return false;

    int numPatients = this->getSize();
    Patient* candidates[100];  // assuming at most 100 patients
    int priorities[100];
    int candidateCount = 0;

    priQueue<Patient*> tempQueue;
    Patient* current = nullptr;
    int priority = 0;

    // First, collect only patients who haven’t been rescheduled yet
    for (int i = 0; i < numPatients; ++i) {
        this->dequeue(current, priority);

        // Save eligible patient
        if (!current->didResc()) {
            candidates[candidateCount] = current;
            priorities[candidateCount++] = priority;
        }

        // Store all patients temporarily
        tempQueue.enqueue(current, priority);
    }

    // Restore the original queue
    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(current, priority);
        this->enqueue(current, priority);
    }

    // If no eligible patients found, return false
    if (candidateCount == 0) return false;

    // Pick one of the eligible patients at random
    int randomIndex = rand() % candidateCount;
    Patient* selected = candidates[randomIndex];

    int oldPT = selected->getappointmentTime();
    int newPT = oldPT + (rand() % 10 + 1); // Shift forward by 1–10 units

    // Try to reschedule with the new appointment time
    bool rescheduled = this->reschedule(selected, newPT);
    if (rescheduled) {
        selected->setRescStatus(true);  // mark as already rescheduled
    }

    return rescheduled;
}


