#pragma once
#include "EU_WaitList.h"
#include "ArrayStack.h"
class X_WaitList : public EU_WaitList {
public:
    void CancelAppointment(int patientID, ArrayStack<Patient*>& finishedPatients);
    void randCancelAppointment(int Peancel, ArrayStack<Patient*>& finishedPatients);
};
