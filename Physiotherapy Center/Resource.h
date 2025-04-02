#pragma once
//#include "Patient.h"

class Resource {
protected:
    int ID;
    //Patient* AssignedPatient;

public:
    Resource(int id);
    virtual ~Resource() = default;

    //virtual bool IsAvailable() = 0;
    //virtual void Assign(Patient* p) = 0;
    //virtual Patient* Release() = 0;
    bool IsAvailable();
    void Assign();
    void Release();

    int GetID();
    //Patient* GetAssignedPatient();
};
