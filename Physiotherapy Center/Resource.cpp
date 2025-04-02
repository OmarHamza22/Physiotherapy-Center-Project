#include "Resource.h"

Resource::Resource(int id) : ID(id){}

int Resource::GetID() {
    return ID;
}



Patient* Resource::GetAssignedPatient() {
    return AssignedPatient;
}
