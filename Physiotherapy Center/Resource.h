#pragma once
#include <iostream>
////dont include patient here wtvr happens
// include it in the child-class
//#include "Patient.h"
class Patient;
class Resource {
protected:
    int ID;
    Patient* AssignedPatient;

public:
    Resource(int id);
    virtual ~Resource() = default;

    virtual bool IsAvailable() = 0;
    virtual void Assign(Patient* p) = 0;
    virtual Patient* Release() = 0;
    virtual void print() = 0;

    int GetID();
    Patient* GetAssignedPatient();
};
