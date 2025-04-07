#pragma once

#include "priQueue.h"
#include "Patient.h"

class EarlyPList : public priQueue<Patient*> {
public:
    // Constructor
    EarlyPList();

    // Reschedule function
    bool reschedule(Patient* p, int newPT);
    // random Reschedule
    bool randReschedule(int Presc);
};
