#include "U_device.h"

U_device::U_device(int id) : Resource(id) {}

bool U_device::IsAvailable() {
    return AssignedPatient == nullptr;
}

void U_device::Assign(Patient* p) {
    AssignedPatient = p;
}
//
Patient* U_device::Release() {
    Patient* released = AssignedPatient;
    AssignedPatient = nullptr;
    return released;
}

void U_device::print() { cout << ID; }
