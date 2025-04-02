#include "Resource.h"

Resource::Resource(int id) : ID(id){}

int Resource::GetID() {
    return ID;
}

bool Resource::IsAvailable() {
    return true;
}

void Resource::Assign() {

}

void Resource::Release() {

}

//Patient* Resource::GetAssignedPatient() {
//    return AssignedPatient;
//}
