#pragma once
#include "Treatment.h"
class X_therapy :
    public Treatment
{
public:
    X_therapy(int id, int dur, int assignT, Patient* Pat, Center* C)
        :Treatment(id, "X_therapy", dur, assignT, Pat, C) {}

    bool CanAssign(Resource* Rec) override;
    bool MovetoWait() override;


};

