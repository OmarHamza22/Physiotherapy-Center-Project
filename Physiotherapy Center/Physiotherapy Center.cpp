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
    center.Simulate();

    // Step 4: Print finished patients or final status (optional)
    //UI::PrintFinishedPatients(center.getFinishedPatients());  // Assuming you have a method to get finished patients
   // std::cout << "Simulation complete!" << std::endl;
    
   /*
    Patient* P1=new Patient(1,2,1,'N');
    Patient* P2 = new Patient(2, 4, 2, 'N');
    Patient* P3 = new Patient(3, 5, 3, 'N');
    Patient* P4 = new Patient(4, 6, 4, 'N');
    Patient* P5 = new Patient(5, 10, 4, 'N');



    E_therapy* E;
    U_therapy* U;
    X_therapy* X;

    center.AddToEWait(P1);
    center.AddToUWait(P2);
    center.AddToXWait(P3);
    center.AddToXWait(P4);
    center.AddToEWait(P5);

    P1->setEtt(5);
    P2->setUtt(10);
    P3->setXtt(12);
    P4->setXtt(14);

    center.AddEDevice(1);
    center.AddEDevice(2);
    center.AddUDevice(1);
    center.AddUDevice(2);

    center.AddXRoom(1, 2);
    //center.AddXRoom(2, 4);


    center.Assign_E();
    center.Assign_U();
    center.Assign_X();
    center.Assign_X();

    P1->printPatientInfo();
    P2->printPatientInfo();
    P3->printPatientInfo();
    P4->printPatientInfo();
    
    center.printDeviceAndRoomLists();
    center.printWaitingList();
    */
    

    return 0;  // Indicate successful execution
}