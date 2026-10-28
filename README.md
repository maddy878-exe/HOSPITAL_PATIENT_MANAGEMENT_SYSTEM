# Hospital Patient Management System

A menu-driven C program that manages a hospital's waiting queue using a circular queue and a `struct Patient`.

## Features

- Add a patient with ID, name, age, and problem
- Prevent duplicate patient IDs among patients currently waiting
- Call the next patient in first-in, first-out (FIFO) order
- Display all waiting patients
- Search for a patient by ID
- Count waiting patients
- Store up to 100 waiting patients

## Requirements

- Visual Studio Code
- A C compiler such as GCC
- The VS Code C/C++ extension (recommended)

## Compile and run

Open this folder in VS Code, then open the integrated terminal.

### Windows (GCC / MinGW)

```bash
gcc main.c -o hospital
.\hospital.exe
```

### Linux / macOS

```bash
gcc main.c -o hospital
./hospital
```

## Example workflow

1. Select `1` to add a patient.
2. Enter the patient's ID, name, age, and problem.
3. Select `3` to display the waiting queue.
4. Select `2` to call the next patient.
5. Select `6` to exit.

## Data structure

The program uses a circular queue implemented with an array. Patients are called in FIFO order: the first patient added is the first patient called. Patient records are kept in memory only and are cleared when the program exits.

## GitHub upload

Create a new empty repository on GitHub. In the VS Code terminal, from this project folder, run:

```bash
git init
git add .
git commit -m "Add hospital patient management system"
git branch -M main
git remote add origin https://github.com/YOUR-USERNAME/YOUR-REPOSITORY.git
git push -u origin main
```

Repository Link:https://github.com/maddy878-exe/HOSPITAL_PATIENT_MANAGEMENT_SYSTEM
