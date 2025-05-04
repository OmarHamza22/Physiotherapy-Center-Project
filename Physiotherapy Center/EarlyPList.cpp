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
    if (roll >= Presc || this->isEmpty()) return false;

    int numPatients = this->getSize();
    int index = rand() % numPatients;

    priQueue<Patient*> tempQueue;
    Patient* selected = nullptr;
    Patient* current = nullptr;
    int priority = 0;

    // Extract all patients, remember the one at the random index
    for (int i = 0; i < numPatients; ++i) {
        this->dequeue(current, priority);
        if (i == index) {
            selected = current;
        }
        tempQueue.enqueue(current, current->getappointmentTime());
    }

    // Restore the original queue
    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(current, priority);
        this->enqueue(current, priority);
    }

    if (!selected) return false;

    int oldPT = selected->getappointmentTime();
    int newPT = oldPT + (rand() % 10 + 1);

    bool rescheduled = this->reschedule(selected, newPT);
    if (rescheduled) {
        selected->setRescStatus(true);
    }

    return rescheduled;
}


