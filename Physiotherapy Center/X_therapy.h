#pragma once
// #include "Center.h"
#include "Treatment.h"
class Center;
class X_therapy :
    public Treatment
{
    Center* center;
public:
    X_therapy(int id, int dur, int assignT)
        :Treatment(id, "X_therapy", dur, assignT)  {}
    X_therapy(Center* C) : Treatment(1, "X_therapy", 5, 0) { center = C; }
    bool CanAssign(Resource* Rec) override;
    bool MovetoWait(Patient* P) override;


};

