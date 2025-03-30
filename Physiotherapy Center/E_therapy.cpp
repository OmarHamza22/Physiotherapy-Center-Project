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

bool E_therapy::MovetoWait()
{
	if (GetCenter())
	{
		//GetCenter->AddtoWait_E(this);
		return true;
	}
	else
	{
		return false;
	}
}
