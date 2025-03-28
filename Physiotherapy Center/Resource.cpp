#include "Resource.h"



////////////////////////////////////////////////////
/// dont forget to re calculate the priority
////////////////////////////////////////////////////

//temp functions:
////////////////////////////////////////////////////

////////////////////////////////////////////////////

Resource::Resource(int id, char type, int capacity) : ID(id), Type(type), AssignedPatient(nullptr), Capacity(capacity), CurrentOccupancy(0) {}

bool Resource::IsAvailable() {
    return (Type == 'X') ? (CurrentOccupancy < Capacity) : (AssignedPatient == nullptr);
}

void Resource::Assign(Patient* p) {
    if (Type == 'X') {
        if (CurrentOccupancy < Capacity) {
            roomQueue.enqueue(p, p->GetArrivalTime() + p->GetServingTime());
            CurrentOccupancy++;
        }
    } else {
        AssignedPatient = p;
    }
}

Patient* Resource::Release() {
    Patient* releasedPatient = nullptr;
    if (Type == 'X') {
        if (CurrentOccupancy > 0) { // Instead of checking IsEmpty()
            int priority;
            if (roomQueue.dequeue(releasedPatient, priority)) {
                CurrentOccupancy--;
            }
        }
    } else {
        releasedPatient = AssignedPatient;
        AssignedPatient = nullptr;
    }
    return releasedPatient;
}

int Resource::GetID() {
    return ID;
}

char Resource::GetType() {
    return Type;
}

Patient* Resource::GetAssignedPatient() {
    return AssignedPatient;
}

int Resource::GetCapacity() {
    return (Type == 'X') ? Capacity : 1;
}

int Resource::GetCurrentOccupancy() {
    return (Type == 'X') ? CurrentOccupancy : (AssignedPatient ? 1 : 0);
}