#pragma once
#include<string>
#include <iostream>
#include"Resource.h"
#include"Center.h"
#include"Patient.h"
using namespace std;
class Patient;
class Center;
class Resource;
class Treatment
{
private:
	int TreID;
	string TreType;
	int duration;
	int assignmentTime;
	Patient* patient;
	Resource* assignresource;
	Center* center;
public:
	Treatment(int id,string type,int dur,int assitime,Patient* Pat,Center* C)
		:TreID(id),TreType(type),duration(dur),assignmentTime(assitime), patient(Pat), assignresource(nullptr),center(C)
	{}

	//setters
	void SetID(int id);
	void SetType(string type);
	void SetPatient(Patient* Pat);
	void SetResources(Resource* Rec);
	void SetDuration(int D);
	void SetAssiTime(int T);


	//getters
	int GetTreID();
	string GetTreType();
	Patient* GetPatient();
	Center* GetCenter();
	int GetDuration();
	int GetAssiTime();


	void PrintInfo();

	virtual bool CanAssign(Resource* Rec);
	virtual bool MovetoWait();
};

