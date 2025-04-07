#pragma once
#include "Resource.h"
#include "priQueue.h"
#include "Patient.h"
#include <istream>

class X_room : public Resource {
private:
    int Capacity;
    int CurrentOccupancy;
    priQueue<Patient*> roomQueue;

public:
    X_room(int id, int capacity);
    bool IsAvailable() override;
    void Assign(Patient* p) override;
    Patient* Release() override;
    int GetCapacity();
    int GetCurrentOccupancy();
    void print()override;
};

