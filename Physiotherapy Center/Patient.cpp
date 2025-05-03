#include "Patient.h"
using namespace std;

  
Patient::Patient(int id, int appointmentTime, int arrivalTime, char Ptype)
{
	ID = id;
	PT = appointmentTime;
	VT = arrivalTime;
	FT  = 0;
	TT = 0;
	TW = FT-(TT+VT);
	Ett = 0;
	Utt = 0;
	Xtt = 0;
	patientType = Ptype;
	assignedResource = nullptr;
	DummbellTime = 0;
	TreadmillTime = 0;
	FoamRollerTime = 0;

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

void Patient::removeXTreatment()
{
	LinkedQueue <Treatment*> temp;
	Treatment* T;
	if (requiredTools.isEmpty())
	{
		while (!requiredTreatments.isEmpty())
		{
			requiredTreatments.dequeue(T);

			if (T->GetTreType() == "X_therapy")
			{
				return;
			}
			else
			{
				temp.enqueue(T);
				
			}
			
		}

		while (!temp.isEmpty())
		{
			temp.dequeue(T);
			requiredTreatments.enqueue(T);
		}
	}
}

void Patient::setappointmentTime(int pt) { PT = pt; }
void Patient::setfinishTime(int t) { FT = t; }
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
void Patient::setDubmbellTime(int time)
{
	DummbellTime = time;
	updateTreatmentTime();
}
void Patient::setTreadmillTime(int time)
{
	TreadmillTime = time;
	updateTreatmentTime();
}
void Patient::setFoamRollerTime(int time)
{
	FoamRollerTime = time;
	updateTreatmentTime();
}
void Patient::updateTreatmentTime()
{
	TT = Ett + Utt + Xtt + DummbellTime + TreadmillTime + FoamRollerTime;
}
void Patient::addtool(Resource* tool)
{
	requiredTools.enqueue(tool);
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
	updateTreatmentTime();
}

void Patient::setUtt(int ut)
{
	Utt = ut;
	updateTreatmentTime();
}

void Patient::setXtt(int xt)
{
	Xtt = xt;
	updateTreatmentTime();
}



// Getters
int Patient::getID() { return ID; }
int Patient::getappointmentTime() { return PT; }
int Patient::getarrivalTime() { return VT; }
int Patient::getfinishTime() { return FT; }
int Patient::gettreatmentTime() {return Ett + Utt + Xtt + DummbellTime + TreadmillTime + FoamRollerTime;}
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




bool Patient::addTreatment(Treatment* treatment) {
	if (requiredTreatments.getSize() < 3) {
		requiredTreatments.enqueue(treatment);
		return true;
	}
	else
	{
		return false;
	}
}

int Patient::getServingTime()
{
    return ST;
}

// bool Patient::completeTreatment() {
//     if (requiredTreatments.isEmpty()) {
        
//         return true; // No treatments left, exit the function
//     }

//     // Retrieve and complete the first treatment
//     Treatment* completed = nullptr;
//     requiredTreatments.dequeue(completed); 

//     cout << "Patient " << ID << " has completed a treatment." << endl;
// }


void Patient::printPatientInfo() const {
	cout << "Patient ID: " << ID //<< "\n"
		//<< "Processing Time: " << PT << "\n"
		//<< "Visit Time: " << VT << "\n"
		//<< "Finish Time: " << FT << "\n"
		<< " ,Treatment Time: " << TT //<< "\n"
			//<< "Time Wait: " << TW << "\n"
			<< " ,Status: " << status << "\n";
	}
bool Patient::hasTreatmentsLeft() const {
	return !requiredTreatments.isEmpty();
}

void Patient::printRequiredTreatments() const {
    cout << "Patient " << ID << "  Required Treatments: " << endl;
    if (requiredTreatments.isEmpty()) {
        cout << "No treatments left." << endl;
    }
    else {
        LinkedQueue<Treatment*> tempQueue = requiredTreatments;  // Create a copy of the queue
        Treatment* t = nullptr;

        // Loop through and print each treatment in the queue
        while (!tempQueue.isEmpty()) {
            tempQueue.peek(t);  // Peek at the front element to get the treatment without removing it
            cout << " Treatment duration: " << t->GetDuration() << endl;
            tempQueue.dequeue(t);  // Remove the treatment from the queue
        }
    }
}


	
int Patient::getRequiredTreatmentsNum(){return requiredTreatments.getSize();}

int Patient::getDummbellTime()
{
	return DummbellTime;
}

int Patient::getTreadmillTime()
{
	return TreadmillTime;
}

int Patient::getFoamRollerTime()
{
	return FoamRollerTime;
}

int Patient::getLastAddedTime()
{
	return LastAddedTime;
}

void Patient::setLastAddedTime(int time)
{
	LastAddedTime = time;
}

void Patient::print() const
{
	cout <<"P"<< ID;
}

void Patient::printDetailed() const
{
	cout <<"P"<< ID <<"_"<< VT;
}

LinkedQueue<Treatment*> Patient::getRequiredTreatments()
{
		return requiredTreatments;
}

LinkedQueue<Resource*> Patient::getRequiredTools()
{
	return requiredTools;
}

Resource* Patient::getAssignedResource()
{
	return assignedResource;
}

void Patient::setAssignedResource(Resource* resource)
{
	assignedResource = resource;
}

Treatment *Patient::getNextTreatment()
{
	Treatment *t;
	if (!requiredTreatments.isEmpty())
	{
		requiredTreatments.dequeue(t);
		return t;
	}
	else
	{
		return nullptr;
	}

}

Resource *Patient::getNextTool()
{
    Resource* R;
	if (requiredTools.isEmpty())
	{
		return nullptr;
	}
		requiredTools.dequeue(R);
		return R;
}
