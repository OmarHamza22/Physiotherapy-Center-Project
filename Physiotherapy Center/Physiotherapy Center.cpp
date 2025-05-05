#include "Center.h"
#include "UI.h"
#include <iostream>

int main() {
    // Step 1: Initialize the Center object
    Center center;

    // Step 2: Load all the necessary data
    //std::string filename = "data";  // Specify your data file (without extension)
    //if (!center.LoadALL(filename)) {
    //    std::cerr << "Error loading data. Exiting program." << std::endl;
    //    return -1;  // Return an error code if loading fails
    //}


    // Step 3: Run the simulation
    //center.Simulate();
    center.MainSimulation();

	center.save("test Final 1"); // Save the simulation results to a file
    // Step 4: Print finished patients or final status (optional)
    //UI::PrintFinishedPatients(center.getFinishedPatients());  // Assuming you have a method to get finished patients
   // std::cout << "Simulation complete!" << std::endl;
    
   /*
    Patient* P1=new Patient(1,2,1,'N');
    Patient* P2 = new Patient(2, 4, 2, 'N');
    Patient* P3 = new Patient(3, 5, 3, 'N');
    Patient* P4 = new Patient(4, 6, 4, 'N');
    Patient* P5 = new Patient(5, 10, 4, 'N');
    Patient* P6 = new Patient(6, 11, 5, 'N');
    Patient* P7 = new Patient(7, 12, 6, 'N');
    Patient* P8 = new Patient(8, 13, 7, 'N');
	Patient* P9 = new Patient(9, 14, 8, 'N');
	Patient* P10 = new Patient(10, 15, 9, 'N');





    E_therapy* E;
    U_therapy* U;
    X_therapy* X;

    center.AddToEWait(P1);
    center.AddToUWait(P2);
    //center.AddToXWait(P3);
    //center.AddToXWait(P4);
    center.AddToEWait(P5);
	center.AddToDumbbellWait(P3);
	center.AddToFoamRollerWait(P4);
	center.AddToTreadmillWait(P6);
	center.AddToFoamRollerWait(P7);
	center.AddToDumbbellWait(P8);
	center.AddToDumbbellWait(P9);
	center.AddToFoamRollerWait(P10);

    P1->setEtt(5);
    P2->setUtt(10);
    //P3->setXtt(12);
    //P4->setXtt(14);
	P3->setDubmbellTime(5);
	P4->setFoamRollerTime(10);
	P5->setEtt(15);
	P6->setTreadmillTime(20);
	P7->setDubmbellTime(25);
	P8->setDubmbellTime(30);
	P9->setFoamRollerTime(35);
	P10->setFoamRollerTime(40);

    center.AddEDevice(1);
    center.AddEDevice(2);
    center.AddUDevice(1);
    center.AddUDevice(2);

   // center.AddXRoom(1, 3);
    //center.AddXRoom(2, 4);
    
	Dumbbell* D1 = new Dumbbell(1);
	Dumbbell* D2 = new Dumbbell(2);
	FoamRoller* F1 = new FoamRoller(1);
	FoamRoller* F2 = new FoamRoller(2);
	Treadmill* T1 = new Treadmill(1);

     
    X_room* X1 = new X_room(1, 5);

	X1->AddDumbbell(D1);    
	X1->AddDumbbell(D2);
	X1->AddFoamRoller(F1);
	X1->AddFoamRoller(F2);
	X1->AddTreadmill(T1);
    

	center.AddXRoom(X1);

    center.Assign_E();

    center.Assign_E();
    center.Assign_U();
    //center.Assign_X();
    //center.Assign_X();
	center.Assign_Dumbbell();
	center.Assign_FoamRoller();
	center.Assign_Treadmill();
	center.Assign_Dumbbell();
    center.Assign_FoamRoller();
    center.Assign_FoamRoller();
	center.Assign_Dumbbell();
    center.Assign_FoamRoller();


    P1->printPatientInfo();
    P2->printPatientInfo();
    P3->printPatientInfo();
    P4->printPatientInfo();
	P5->printPatientInfo();
	P6->printPatientInfo();
	P7->printPatientInfo();
	P8->printPatientInfo();
	P9->printPatientInfo();
	P10->printPatientInfo();


    center.printDeviceAndRoomLists();
    center.printWaitingList();

    center.From_INtreatment();
	center.From_INtreatment();
	center.From_INtreatment();
	center.From_INtreatment();
    center.From_INtreatment();
    center.From_INtreatment();
    center.From_INtreatment();

    center.printDeviceAndRoomLists();
    center.printWaitingList();
    center.printFinishedPatient();
    
    P1->printPatientInfo();
    P2->printPatientInfo();
    P3->printPatientInfo();
    P4->printPatientInfo();
    P5->printPatientInfo();
    P6->printPatientInfo();
    P7->printPatientInfo();
    P8->printPatientInfo();
    P9->printPatientInfo();
    P10->printPatientInfo();
    */
    return 0;  // Indicate successful execution
}