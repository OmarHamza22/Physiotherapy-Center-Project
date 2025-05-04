#pragma once
#include "EU_WaitList.h"
#include "ArrayStack.h"
class X_WaitList : public EU_WaitList {
public:
    void CancelAppointment(Patient* targetPatient, ArrayStack<Patient*>& finishedPatients, int timestep);
    void randCancelAppointment(int Peancel, ArrayStack<Patient*>& finishedPatients, int timestep);
};
