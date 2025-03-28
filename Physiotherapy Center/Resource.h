#pragma once

#include "Patient.h"

class Resource {
private:
    int ID;
    char Type; // 'E' : Electro, 'U' : Ultrasound, 'X' : gym room
    Patient* AssignedPatient;

public:
    Resource(int id, char type);

    bool IsAvailable() const;
    void Assign(Patient* p);
    void Release();

    int GetID() const;
    char GetType() const;
    Patient* GetAssignedPatient() const;
};  

