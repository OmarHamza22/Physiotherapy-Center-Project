#include "X_therapy.h"

bool X_therapy::CanAssign(Resource* Rec)
{
	if (Rec && Rec->IsAvailable() && Rec->GetType() == 'X')//checks for capacity Rec->HasCapacity()
	{
		SetResources(Rec);
		return true;
	}
	else
	{
		return false;
	}
}

bool X_therapy::MovetoWait()
{
	if (GetCenter())
	{
		//GetCenter->AddtoWait_X(this);
		return true;
	}
	else
	{
		return false;
	}
}
