# Physiotherapy Center Project

Welcome to the **Physiotherapy Center Project** by Omar Hamza!  
This simulation models a physiotherapy center’s operations using custom data structures—built as part of a Data Structures & Algorithms course project.

---

## 📂 Repository
**GitHub:** [Physiotherapy-Center-Project](https://github.com/OmarHamza22/Physiotherapy-Center-Project)

---
## 📌 Overview
- **Language:** C++  
- Simulates appointment systems for **Normal (N)** and **Recovering (R)** patients.  
- Manages early, on-time, and late arrivals, resource allocation, cancellations, and rescheduling.  
- Demonstrates practical use of **Queue**, **Stack**, and **Priority Queue** data structures.  

---

## 🎯 Objectives
- Handle patient flow: Early, Waiting, In-Treatment, Finished lists.  
- Allocate Electro, Ultrasound, and Gym resources dynamically.  
- Process cancellations (X-therapy) and rescheduling (probabilistically).  
- Provide detailed end-of-simulation reports with performance statistics.  
---


## 🧑‍🤝‍🧑 Main Entities
- **Patients**
  - Patient ID (PID)
  - Patient Type: Normal (N) or Recovering (R)
  - Appointment Time (PT), Arrival Time (VT)
  - Required Treatments List
  - Patient Status: IDLE, ERLY, LATE, WAIT, SERV, FNSH

- **Treatments**
  - Electro-therapy (E)
  - Ultrasound-therapy (U)
  - Exercises in a Gym room (X)

- **Resources**
  - Electro devices
  - Ultrasound devices
  - Gym rooms (with capacity)

---

## 📝 Key Definitions
- **Simulation Time (timestep):** Counter starting at 1, incremented after each event.
- **Waiting Time (WT):** Time patient spends waiting before treatment.
- **Treatment Time (TT):** Total time patient spends in treatments.
- **Finish Time (FT):** `FT = VT + WT + TT`

---

## 📂 System Lists
1. ALL Patients  
2. Early Patients  
3. Late Patients  
4. Waiting Patients (E, U, X)  
5. In-Treatment Patients  
6. Finished Patients  
7. Available Resources (devices & rooms)

---

## 📖 Project Phases
### Phase 1.1 (10%)
- Select appropriate data structures (Queue, Stack, Priority Queue).
- Justify choices for each list (early, late, waiting, etc.).

### Phase 1.2 (30%)
- Implement & test data structures.
- Implement file loading function.
- Build a **simple simulator** for moving patients between lists.
- Deliverables:
  - Code (no executables)
  - Sample input file
  - Demo video (<10 minutes)

### Phase 2 (60%)
- Extend Phase 1 to full system.
- Implement:
  - Scheduling logic
  - Treatment assignment
  - Resource management
  - Output file generation
- Deliverables:
  - Final code
  - Six sample input/output files
  - Workload distribution doc
  - Final output report

---

## ⚙️ Rules & Restrictions
- Only **Stack, Queue, Priority Queue** (or derived) are allowed.
- No STL containers.
- No global variables.
- No unauthorized friendships (only for `operator<<` where required).
- Patients should be moved between lists via **pointers** (no deep copies).

---
---

## 📁 File Structure
```
├── .vscode/                       
├── Physiotherapy Center.sln       # Visual Studio solution
├── Physiotherapy-Center-Project.rar # Project archive (source and files)
├── ID.txt                         
├── Omar.txt                       
├── src/ (if extracted)            # Source code files
└── README.md                      
```

---

## 📥 Input File Format
1. Number of devices/rooms:
   ```
   NE NU NG
   ```
2. Room capacities.
3. Probabilities (Pcancel, Presc).
4. Number of patients.
5. Patient details:
   ```
   <Type> <PT> <VT> <NT> [<TreatmentType> <Duration>]...
   ```

**Example:**
```
3 1 2
10 5
10 30
4
N 30 25 3 E 5 U 12 X 10
R 30 35 3 U 6 E 5 X 10
R 50 40 1 X 5
N 40 40 2 X 15 U 10
```

---

## 📤 Output File Format (Phase 2)
For each patient:
```
PID  PType  PT  VT  FT  WT  TT  Cancel  Resc
```

Then system statistics:
- Total timesteps
- Total patients, N-patients, R-patients
- Average waiting & treatment times
- Cancellation & rescheduling percentages
- Early & late patient percentages
- Average late penalty

---

## 🖥 Program Interface
Two modes:
1. **Interactive Mode** – Step-by-step console output, showing lists & resources.
2. **Silent Mode** – Runs simulation silently, outputs only final results file.



## 🔗 Repository
[GitHub: Physiotherapy-Center-Project](https://github.com/OmarHamza22/Physiotherapy-Center-Project)

---
