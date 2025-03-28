#pragma once
#include "Treatment.h"
class U_therapy :
    public Treatment
{
public:
    U_therapy(int id,int dur,int assignT,Patient* Pat,Center* C)
        :Treatment(id,"U_therapy",dur,assignT,Pat,C){ }

    bool CanAssign(Resource* Rec) override;
    bool MovetoWait() override;

};

