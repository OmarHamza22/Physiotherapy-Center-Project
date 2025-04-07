#pragma once
#include "Treatment.h"
class Center;
class E_therapy :
	public Treatment
{
	Center* center;

public:
	E_therapy(int id, int dur, int assignT)
		:Treatment(id, "E_therapy", dur, assignT) {}

	bool CanAssign(Resource* Rec) override;
	bool MovetoWait(Patient* P) override;
};

