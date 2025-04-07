#include "Patient.h"
using namespace std;

  
Patient::Patient(int id, int appointmentTime, int arrivalTime, char Ptype)
{
	ID = id;
	PT = appointmentTime;
	VT = arrivalTime;
	FT  = VT + TT + TW;
	TT = 0;
	TW = 0;
	Ett = 0;
	Utt = 0;
	Xtt = 0;
	patientType = Ptype;
	if (VT > PT)
	{
		status = "Late";
	}
	else if  (VT<PT)
	{
		status = "ERLY";
	}
	else
	{
		status = "UNKOWN";
	}

}

//setters

void Patient::setappointmentTime(int pt) { PT = pt; }
void Patient::setfinishTime() { FT = VT+TT+TW; }
void Patient::settreatmentTime(int tt) { TT = Ett+Xtt+Utt; }
void Patient::setwaitingTime(int tw) { TW = TW+tw; }
void Patient::setStatus(string newStatus) { status = newStatus; }
void Patient::setPatientType(char type) {
	if (type == 'N' || type == 'R') {
		patientType = type;
	}
	else {
		cout << "Invalid patient type! Use 'N' for Normal or 'R' for Recovering." << endl;
	}
}
void Patient::setsortValue()
{
	if (status == "Late")
	{
		sortingValue = PT + getPenalty();
	}
	else
	{
		sortingValue = PT;
	}
}

void Patient::setEtt(int et)
{
	Ett = et;
}

void Patient::setUtt(int ut)
{
	Utt = ut;
}

void Patient::setXtt(int xt)
{
	Xtt = xt;
}



// Getters
int Patient::getID() { return ID; }
int Patient::getappointmentTime() { return PT; }
int Patient::getarrivalTime() { return VT; }
int Patient::getfinishTime() { return FT; }
int Patient::gettreatmentTime() { return TT; }
int Patient::getwaitingTime() { return TW; }
string Patient::getStatus() { return status; }
char Patient::getPatientType() const { return patientType; }

int Patient::getPenalty()
{
	int penalty;
	if (PT<VT)
	{
		penalty = (VT - PT) / 2;
	}
	else
	{
		penalty = 0;
	}
	
	return penalty;

}

int Patient::getsortValue()
{
	return sortingValue;
}

int Patient::getEtt()
{
	return Ett;
}

int Patient::getUtt()
{
	return Utt;
}

int Patient::getXtt()
{
	return Xtt;
}






void Patient::printPatientInfo() const {
		cout << "Patient ID: " << ID << "\n"
			<< "Processing Time: " << PT << "\n"
			<< "Visit Time: " << VT << "\n"
			<< "Finish Time: " << FT << "\n"
			<< "Treatment Time: " << TT << "\n"
			<< "Time Wait: " << TW << "\n"
			<< "Status: " << status << "\n";
	}
bool Patient::hasTreatmentsLeft() const {
	return !requiredTreatments.empty();
}
void Patient::printRequiredTreatments() const {
	cout << "Patient " << ID << "  Required Treatments: " << endl;
	if (requiredTreatments.empty()) {
		cout << "No treatments left." << endl;
	}
	else {
		queue<Treatment*> tempQueue = requiredTreatments; 
		while (!tempQueue.empty()) {
			Treatment* t = tempQueue.front();
			cout << " Treatment duration: " << t->GetDuration() <<  endl;
			tempQueue.pop();
		}
	}
}

bool Patient::addrequiredTreatment(Treatment* treatment) {
	if (requiredTreatments.size() < 3) {
		requiredTreatments.push(treatment);
		return true;
	}
	return false;
}

Treatment* Patient::getNextRequiredTreatment() 
{
	if (!requiredTreatments.empty()) {
		Treatment* T = requiredTreatments.front();
		requiredTreatments.pop();
		return T;
	}
}

Treatment* Patient::getAndRemoveNextRequiredTreatment() {
	if (!requiredTreatments.empty()) {
		Treatment* T = requiredTreatments.front();
		requiredTreatments.pop();
		return T;
	}
	return nullptr;
}



////std::ostream& operator<<(std::ostream& os, Patient* p) {
//	os << "P" << p->get_PID() << "_" << p->get_VT();
//	return os;
//}

