#include "FoamRoller.h"

FoamRoller::FoamRoller(int id) : Resource(id) {}
bool FoamRoller::IsAvailable()
{
    return AssignedPatient == nullptr;
}
void FoamRoller::Assign(Patient* p) {
    AssignedPatient = p;
}
Patient* FoamRoller::Release() {
    Patient* released = AssignedPatient;
    AssignedPatient = nullptr;
    return released;
}
void FoamRoller::print() { cout << ID; }