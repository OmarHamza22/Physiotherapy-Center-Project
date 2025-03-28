#pragma once

#include "Patient.h"
#include "priQueue.h"

class Resource {
private:
    int ID;
    char Type; // 'E' : Electro, 'U' : Ultrasound, 'X' : Room
    Patient* AssignedPatient;
    int Capacity; 
    priQueue<Patient*> roomQueue;
    int CurrentOccupancy; 

public:
    Resource(int id, char type, int capacity = 1);

    bool IsAvailable();
    void Assign(Patient* p);
    Patient* Release();

    int GetID();
    char GetType();
    Patient* GetAssignedPatient();
    int GetCapacity();
    int GetCurrentOccupancy();
};