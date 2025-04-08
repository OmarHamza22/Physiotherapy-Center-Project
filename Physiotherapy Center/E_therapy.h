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
		E_therapy() : Treatment(1, "E_therapy", 5, 0) {}
	bool CanAssign(Resource* Rec) override;
	bool MovetoWait(Patient* P) override;
};

