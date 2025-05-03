#pragma once

#include <iostream>
#include <string>
#include "Treatment.h"
#include "LinkedQueue.h"
#include "ArrayStack.h"
using namespace std;
class Patient
{
private:
    int ID;
    int PT;// apoint
    int VT;//arrival
    int FT;// finish
    int TT;//total treatment time
    int TW;//wait time
    int sortingValue;
    string status;
    int Ett;
    int Utt;
    int Xtt;
    char patientType;
    int DummbellTime=0;
    int TreadmillTime=0;
    int FoamRollerTime=0;
    int LastAddedTime;
    int ST = VT+getPenalty();
    bool RescBool = false;
    bool CancelBool = false;
	Resource* assignedResource;

    LinkedQueue<Treatment*> requiredTreatments;
    //ArrayStack<Treatment*> finishedTreatments;
	LinkedQueue<Resource*> requiredTools;

public:
    //constructor
    Patient(int id, int appointmentTime, int arrivalTime, char Ptype);
 
    //setters 

    ///
    void removeXTreatment();
    ////

    void setappointmentTime(int pt);
    void setfinishTime(int t);
    void settreatmentTime(int tt);
    void setwaitingTime(int tw);
    void setStatus(string newStatus);
    void setsortValue();
    void setEtt(int et);
    void setUtt(int ut);
    void setXtt(int xt);
    void setPatientType(char type);
	void setDubmbellTime(int time);
	void setTreadmillTime(int time);
	void setFoamRollerTime(int time);
    void updateTreatmentTime();
void addtool(Resource* tool);
    //getters
    int getID();
    int getappointmentTime();
    int getarrivalTime();
    int getfinishTime();
    int gettreatmentTime();
    int getwaitingTime();
    string getStatus();
    int getPenalty();
    int getsortValue();
    int getEtt();
    int getUtt();
    int getXtt();
    char getPatientType() const;
    int getRequiredTreatmentsNum();
	int getDummbellTime();
	int getTreadmillTime();
	int getFoamRollerTime();
	int getLastAddedTime() ;
    void setLastAddedTime(int time);
    bool addTreatment(Treatment* treatment);
    int getServingTime();
    //bool completeTreatment();
    bool hasTreatmentsLeft() const;
    void printPatientInfo() const;
    void printRequiredTreatments() const;
    void print() const;
    void printDetailed() const;

    LinkedQueue<Treatment*> getRequiredTreatments();
	LinkedQueue<Resource*> getRequiredTools();
	Resource* getAssignedResource();
    void setAssignedResource(Resource* resource); 
    ///Eyad:
    Treatment* getNextTreatment();
    Resource* getNextTool(); 
    Treatment* peekNextTreatment();
    Resource* peekNextTool();
    bool didResc();
    bool didCancel();
    void setRescStatus(bool x);
    void setCancelStatus(bool x);
}; 
