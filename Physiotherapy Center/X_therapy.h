#pragma once
#include "Treatment.h"
class Center;
class X_therapy :
    public Treatment
{
    Center* center;
public:
    X_therapy(int id, int dur, int assignT)
        :Treatment(id, "X_therapy", dur, assignT)  {}

    bool CanAssign(Resource* Rec) override;
    bool MovetoWait(Patient* P) override;


};

