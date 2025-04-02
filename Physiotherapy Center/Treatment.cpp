#include "Treatment.h"

using namespace std;

void Treatment::SetDuration(int D)
{
	duration = D;
}

void Treatment::SetAssiTime(int T)
{
	assignmentTime = T;
}

void Treatment::SetID(int id)
{
	TreID = id;
}

void Treatment::SetType(string type)
{
	TreType = type;
}

void Treatment::SetResources(Resource* Rec)
{
	assignresource = Rec;
}

int Treatment::GetTreID()
{
	return TreID;
}

string Treatment::GetTreType()
{
	return TreType;
}

int Treatment::GetDuration()
{
	return duration;
}

int Treatment::GetAssiTime()
{
	return assignmentTime;
}

void Treatment::PrintInfo()
{
	cout << "Treatment ID: " << TreID << endl;
	cout << "Treatment Type: " << TreType << endl;
	cout << "Assighnment Time: " << assignmentTime << endl;
	cout << "Duration: " << duration << endl;

}

bool Treatment::CanAssign(Resource* Rec)
{
	if (Rec->IsAvailable() )
	{
		assignresource = Rec;
		return true;
		
	}
	else
	{
		return false;
	}
}