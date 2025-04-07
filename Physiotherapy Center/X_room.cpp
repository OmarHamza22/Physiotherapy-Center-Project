#include "X_room.h"

X_room::X_room(int id, int capacity) : Resource(id), Capacity(capacity), CurrentOccupancy(0) {}

bool X_room::IsAvailable() {
    return CurrentOccupancy < Capacity;
}

void X_room::Assign(Patient* p) {
    if (IsAvailable()) {
        roomQueue.enqueue(p, p->getarrivalTime() + p->getXtt());
        CurrentOccupancy++;
    }
}
//
Patient* X_room::Release() {
    Patient* releasedPatient = nullptr;
    int priority;
    if (roomQueue.dequeue(releasedPatient, priority)) {
        CurrentOccupancy--;
    }
    return releasedPatient;
}

int X_room::GetCapacity() {
    return Capacity;
}

int X_room::GetCurrentOccupancy() {
    return CurrentOccupancy;
}

void X_room::print()
{
    cout<<"R" << ID << "[" << CurrentOccupancy <<"," << Capacity << "]"; 
}
