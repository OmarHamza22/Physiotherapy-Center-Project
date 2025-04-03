#include "X_therapy.h"

bool X_therapy::CanAssign(Resource* Rec)
{
	if (Rec && Rec->IsAvailable())//checks for capacity Rec->HasCapacity()  && Rec->GetType() == 'X'
	{
		SetResources(Rec);
		return true;
	}
	else
	{
		return false;
	}
}

bool X_therapy::MovetoWait(Patient* P)
{
	if (center && CanAssign(assignresource))
	{
		//assignresource->setAvalibalit(false);
		//center->addtoE_wait(P);
		return true;
	}
	return false;
}


