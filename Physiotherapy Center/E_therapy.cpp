#include "E_therapy.h"

bool E_therapy::CanAssign(Resource* Rec)
{
	if (Rec && Rec->IsAvailable() ) //Rec == 'E')
	{
		SetResources(Rec);
		return true;
	}
	else
	{
		return false;
	}
}

bool E_therapy::MovetoWait(Patient* P)
{
	if (center && CanAssign(assignresource))
	{
		//assignresource->setAvalibalit(false);
		//center->addtoE_wait(P);
		return true;
	}
	return false;
}


