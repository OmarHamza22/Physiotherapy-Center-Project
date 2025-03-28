#include "Treatment.h"
#include<string>
#include <iostream>
#include"Resource.h"
#include"Center.h"
#include"Patient.h"
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

void Treatment::SetPatient(Patient* Pat)
{
	patient = Pat;
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

Patient* Treatment::GetPatient()
{
	return patient;
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
	if (patient) {
		cout << "Patient ID: " << patient << endl;  // patient->getID to be done
	}
	cout << "Assighnment Time: " << assignmentTime << endl;
	cout << "Duration: " << duration << endl;

}

bool Treatment::CanAssign(Resource* Rec)
{
	if (Rec )//Rec->isAvalibele() to be done
	{
		assignresource = Rec;
		return true;
		
	}
	else
	{
		return false;
	}
}

bool Treatment::MovetoWait()
{
	if (center)
	{
		//center->AddtoWait(this)
		return true;
	}
	else
	{
		return false;
	}
}
