#include "Resource.h"

Resource::Resource(int id) : ID(id), AssignedPatient(nullptr) {}

int Resource::GetID() {
    return ID;
}

Patient* Resource::GetAssignedPatient() {
    return AssignedPatient;
}
