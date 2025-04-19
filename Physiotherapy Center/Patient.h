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
    int PT;
    int VT;
    int FT;
    int TT=Ett+Xtt+Utt;
    int TW;
    int sortingValue;
    string status;
    int Ett;
    int Utt;
    int Xtt;
    char patientType;
    
    LinkedQueue<Treatment*> requiredTreatments;
    //ArrayStack<Treatment*> finishedTreatments;


public:
    //constructor
    Patient(int id, int appointmentTime, int arrivalTime, char Ptype);
 
    //setters 

  

    void setappointmentTime(int pt);
    void setfinishTime();
    void settreatmentTime(int tt);
    void setwaitingTime(int tw);
    void setStatus(string newStatus);
    void setsortValue();
    void setEtt(int et);
    void setUtt(int ut);
    void setXtt(int xt);
    void setPatientType(char type);


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

    bool addTreatment(Treatment* treatment);
    //bool completeTreatment();
    bool hasTreatmentsLeft() const;
    void printPatientInfo() const;
    void printRequiredTreatments() const;
    void print() const;
    void printDetailed() const;


}; 