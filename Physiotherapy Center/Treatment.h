#pragma once
#include<string>
#include <iostream>
#include"Resource.h"
using namespace std;

class Treatment
{
private:
	int TreID;
	string TreType;
	int duration;
	int assignmentTime;
	Resource* assignresource;
public:
	Treatment(int id, string type, int dur, int assitime)
		:TreID(id), TreType(type), duration(dur), assignmentTime(assitime), assignresource(nullptr)
	{
	}

	//setters
	void SetID(int id);
	void SetType(string type);
	void SetResources(Resource* Rec);
	void SetDuration(int D);
	void SetAssiTime(int T);


	//getters
	int GetTreID();
	string GetTreType();
	int GetDuration();
	int GetAssiTime();


	void PrintInfo();

	virtual bool CanAssign(Resource* Rec);
	virtual bool MovetoWait() = 0;
};

