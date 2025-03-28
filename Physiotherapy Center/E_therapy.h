#pragma once
#include "Treatment.h"
class E_therapy :
    public Treatment
{
public:
    E_therapy(int id, int dur, int assignT, Patient* Pat, Center* C)
        :Treatment(id, "E_therapy", dur, assignT, Pat, C) {}

    bool CanAssign(Resource* Rec) override;
    bool MovetoWait() override;
};

