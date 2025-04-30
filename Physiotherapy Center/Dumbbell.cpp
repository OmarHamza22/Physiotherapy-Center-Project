#include "Dumbbell.h"

Dumbbell::Dumbbell(int id) : Resource(id) {}

bool Dumbbell::IsAvailable()
{
	return AssignedPatient == nullptr;
}
void Dumbbell::Assign(Patient* p) {
	AssignedPatient = p;
}
Patient* Dumbbell::Release() {
	if (AssignedPatient!=nullptr)
	{
		Patient* released = AssignedPatient;
		AssignedPatient = nullptr;
		return released;
	}
	else
	{
		return nullptr;
	}
   
}
void Dumbbell::print() { cout << ID; }

