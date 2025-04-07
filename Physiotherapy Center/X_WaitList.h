#pragma once
#include "EU_WaitList.h"
#include "Center.h"
class X_WaitList : public EU_WaitList {
public:
    void CancelAppointment(int patientID);
    void randCancelAppointment(int Peancel);
};

