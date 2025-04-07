#pragma once
#include "Treatment.h"
class Center;
class U_therapy :
    public Treatment
{
    Center* center;

public:
    U_therapy(int id,int dur,int assignT)
        :Treatment(id,"U_therapy",dur,assignT){}

    bool CanAssign(Resource* Rec) override;
    bool MovetoWait(Patient* P) override;

};

