#include "Treadmill.h"

Treadmill::Treadmill(int id) : Resource(id) {}
bool Treadmill::IsAvailable()
{
    return AssignedPatient == nullptr;
}
void Treadmill::Assign(Patient* p) {
    AssignedPatient = p;
}
Patient* Treadmill::Release() {
    Patient* released = AssignedPatient;
    AssignedPatient = nullptr;
    return released;
}
void Treadmill::print() { cout << ID; }