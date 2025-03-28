#include "Resource.h"

Resource::Resource(int id, char type) : ID(id), Type(type), AssignedPatient(nullptr) {}

bool Resource::IsAvailable() const {
    return AssignedPatient == nullptr;
}

void Resource::Assign(Patient* p) {
    AssignedPatient = p;
}

void Resource::Release() {
    AssignedPatient = nullptr;
}

int Resource::GetID() const {
    return ID;
}

char Resource::GetType() const {
    return Type;
}

Patient* Resource::GetAssignedPatient() const {
    return AssignedPatient;
}
