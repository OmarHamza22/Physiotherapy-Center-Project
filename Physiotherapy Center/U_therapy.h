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
    U_therapy(Center* C) : Treatment(1, "U_therapy", 5, 0) { center = C; }
    bool CanAssign(Resource* Rec) override;
    bool MovetoWait(Patient* P) override;

};

