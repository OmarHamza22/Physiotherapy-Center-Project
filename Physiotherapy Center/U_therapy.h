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
        U_therapy() : Treatment(1, "E_therapy", 5, 0) {}
    bool CanAssign(Resource* Rec) override;
    bool MovetoWait(Patient* P) override;

};

