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
    string status;


    queue<Treatment*> requiredTreatments;
    stack<Treatment*> finishedTreatments;


public:
    //constructor
    Patient(int id, int PT, int VT, int FT, int TT, int TW, string stat);

    //setters 

    void setappointmentTime(int pt);
    void setfinishTime(int ft);
    void settreatmentTime(int tt);
    void setwaitingTime(int tw);
    void setStatus(string newStatus);


    //getters
    int getID();
    int getappointmentTime();
    int getarrivalTime();
    int getfinishTime();
    int gettreatmentTime();
    int getwaitingTime();
    string getStatus();


    void addTreatment(Treatment* treatment);
    void completeTreatment();
    bool hasTreatmentsLeft() const;
    void printPatientInfo() const;
    void printRequiredTreatments() const;
    void printFinishedTreatments() const;

}; 