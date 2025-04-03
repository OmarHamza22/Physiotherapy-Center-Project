#pragma once
#include "Treatment.h"
#include "Center.h"
class E_therapy :
	public Treatment
{
	Center* center;

public:
	E_therapy(int id, int dur, int assignT, Center*C)
		:Treatment(id, "E_therapy", dur, assignT) {
		this->center = C;
	}

	bool CanAssign(Resource* Rec) override;
	bool MovetoWait(Patient* P) override;
};

