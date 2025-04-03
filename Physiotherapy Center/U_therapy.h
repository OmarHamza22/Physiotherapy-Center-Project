#pragma once
#include "Treatment.h"
#include "Center.h"
class U_therapy :
    public Treatment
{
    Center* center;

public:
    U_therapy(int id,int dur,int assignT,Center* C)
        :Treatment(id,"U_therapy",dur,assignT){
        this->center = C;
    }

    bool CanAssign(Resource* Rec) override;
    bool MovetoWait(Patient* P) override;

};

