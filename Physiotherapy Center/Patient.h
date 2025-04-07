#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include "Treatment.h"

using namespace std;
class Patient
{
private:
    int ID;
    int PT;
    int VT;
    int FT;
    int TT;
    int TW;
    int sortingValue;
    string status;
    int Ett;
    int Utt;
    int Xtt;
    char patientType;
   

    queue<Treatment*> requiredTreatments;
   


public:
    //constructor
    Patient(int id, int appointmentTime, int arrivalTime,int finishtime, char Ptype);
 
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


    bool addrequiredTreatment(Treatment* treatment);
    Treatment* getNextRequiredTreatment() ;
    Treatment* getAndRemoveNextRequiredTreatment();
    bool hasTreatmentsLeft() const;
    void printPatientInfo() const;
    void printRequiredTreatments() const;

}; 