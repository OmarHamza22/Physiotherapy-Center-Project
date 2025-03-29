#include "Patient.h"
using namespace std;


Patient::Patient(int id, int appointmentTime, int arrivalTime, int finishTime, int treatmentTime, int waitingTime, string stat)
{
	ID = id;
	PT = appointmentTime;
	VT = arrivalTime;
	FT = finishTime;
	TT = treatmentTime;
	TW = waitingTime;
	stat = status;
}
//setters

void Patient::setappointmentTime(int pt) { PT = pt; }
void Patient::setfinishTime(int ft) { FT = ft; }
void Patient::settreatmentTime(int tt) { TT = tt; }
void Patient::setwaitingTime(int tw) { TW = tw; }
void Patient::setStatus(string newStatus) { status = newStatus; }

// Getters
int Patient::getID() { return ID; }
int Patient::getappointmentTime() { return PT; }
int Patient::getarrivalTime() { return VT; }
int Patient::getfinishTime() { return FT; }
int Patient::gettreatmentTime() { return TT; }
int Patient::getwaitingTime() { return TW; }
string Patient::getStatus() { return status; }


void Patient::addTreatment(Treatment* treatment) {
	requiredTreatments.push(treatment);
	cout << "Patient " << ID << " received a new treatment.\n";
}

void Patient::completeTreatment() {
	if (!requiredTreatments.empty()) {
		Treatment* completed = requiredTreatments.front();
		requiredTreatments.pop();
		finishedTreatments.push(completed);
	}
	else {
		cout << "No treatments left for patient " << ID << endl;
	}
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


void Patient::printFinishedTreatments() const {
	cout << "Patient " << ID << "  Finished Treatments: " << endl;
	if (finishedTreatments.empty()) {
		cout << "No treatments completed yet." << endl;
	}
	
