#pragma once
#include "Treatment.h"
#include "Center.h"
class X_therapy :
    public Treatment
{
    Center* center;
public:
    X_therapy(int id, int dur, int assignT, Center* C)
        :Treatment(id, "X_therapy", dur, assignT) 
    {
        this->center = C;
    }

    bool CanAssign(Resource* Rec) override;
    bool MovetoWait() override;


};

