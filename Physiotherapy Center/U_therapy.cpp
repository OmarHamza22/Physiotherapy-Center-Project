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

bool U_therapy::MovetoWait()
{
	if (GetCenter())
	{
		//GetCenter->AddtoWait_U(this);
		return true;
	}
	else
	{
		return false;
	}
}
