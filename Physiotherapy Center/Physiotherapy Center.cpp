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

    return 0;  // Indicate successful execution
}