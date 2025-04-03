#include "U_therapy.h"

bool U_therapy::CanAssign(Resource* Rec)
{
	if (Rec && Rec->IsAvailable() )//&& Rec->GetType() == 'U'
	{
		SetResources(Rec);
		return true;
	}
	else
	{
		return false;
	}
}

bool U_therapy::MovetoWait(Patient* P)
{
	if (center && CanAssign(assignresource))
	{
		//assignresource->setAvalibalit(false);
		//center->addtoU_wait(P);
		return true;
	}
	return false;
}
