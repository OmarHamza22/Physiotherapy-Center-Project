#include "E_device.h"

E_device::E_device(int id) : Resource(id) {}

//bool E_device::IsAvailable()
//{
//    return AssignedPatient == nullptr;
//}
//
//
//
//void E_device::Assign(Patient* p) {
//    AssignedPatient = p;
//}
//
//Patient* E_device::Release() {
//    Patient* released = AssignedPatient;
//    AssignedPatient = nullptr;
//    return released;
//}
