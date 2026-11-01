::: {align="center"}
# HOSPITAL PATIENT MANAGEMENT SYSTEM

### A console-based patient queue management application built with C

A menu-driven application for managing patient registration, waiting
queues, consultations, and records using a circular queue and file
handling.

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c)
![Data
Structure](https://img.shields.io/badge/Data_Structure-Circular_Queue-6A5ACD?style=for-the-badge)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey?style=for-the-badge)
![Project](https://img.shields.io/badge/Project-Academic%20%7C%20Learning-success?style=for-the-badge)

**[Features](#features) \| [How It Works](#how-it-works) \|
[Installation](#installation-and-setup) \| [Usage](#how-to-use) \|
[Project Structure](#project-structure)**
:::

------------------------------------------------------------------------

## About the Project

The **Hospital Patient Management System** is a menu-driven C
programming project designed to organise patients waiting for
consultation.

It uses a **Circular Queue** to maintain the order in which patients are
called. The first patient added is the first patient called, following
the **FIFO (First In, First Out)** principle.

The application demonstrates C structures, functions, input validation,
and file handling. Waiting-patient records can be saved to a file and
loaded again when the program starts. Patients who are called for
consultation are recorded in a separate history file.

> **Academic focus:** This project demonstrates how queue data
> structures can be applied to a patient waiting-list management
> problem.

## Features

  ------------------------------------------------------------------------
                           No. Feature               Description
  ---------------------------- --------------------- ---------------------
                            01 Add Patient           Registers a patient
                                                     and adds them to the
                                                     rear of the queue
                                                     (Enqueue).

                            02 Call Next Patient     Displays and removes
                                                     the patient at the
                                                     front (Dequeue).

                            03 Display Waiting List  Shows all patients
                                                     currently waiting, in
                                                     queue order.

                            04 Search Patient        Finds a waiting
                                                     patient using their
                                                     ID.

                            05 Update Details        Edits the name, age,
                                                     and problem of a
                                                     waiting patient.

                            06 Cancel Patient        Removes a selected
                                                     patient from the
                                                     waiting queue.

                            07 Count Patients        Displays the number
                                                     of waiting patients
                                                     and available spaces.

                            08 Consultation History  Displays the text log
                                                     of patients called
                                                     for consultation.

                            09 Save Records          Saves the current
                                                     waiting list to
                                                     `patients.dat`.

                            10 Exit                  Saves the waiting
                                                     list and closes the
                                                     application.
  ------------------------------------------------------------------------

## Menu Preview

``` text
================================================
        HOSPITAL PATIENT MANAGEMENT SYSTEM
================================================

  1. Add Patient (Enqueue)
  2. Call Next Patient (Pop / Dequeue)
  3. Display Waiting Patients
  4. Search Patient
  5. Update Patient Details
  6. Cancel Patient from Queue
  7. Count Waiting Patients
  8. View Consultation History
  9. Save Patient Records
 10. Exit

 Enter your choice:
```

## How It Works

### 1. Circular Queue and FIFO

A queue follows the **First In, First Out (FIFO)** principle. A patient
who joins the waiting list first will be the next patient called, unless
they are cancelled.

``` text
                 ENQUEUE (ADD)
                       |
                       v
       REAR  +-------------------+
             | Patient C        |
             +-------------------+
             | Patient B        |
             +-------------------+
      FRONT  | Patient A        |
             +-------------------+
                       |
                       v
              DEQUEUE (CALL NEXT)
```

The queue is implemented using an array of 100 patient records. The
`front` index identifies the next patient to be called, while `rear`
identifies the last patient added. Circular indexing allows freed array
positions to be reused.

### 2. Main Program Flow

``` mermaid
flowchart TD
    A([Start]) --> B[Load saved waiting records]
    B --> C[Display main menu]
    C --> D{User choice}
    D -->|1 Add| E[Validate and enqueue patient]
    D -->|2 Call next| F[Dequeue front patient]
    D -->|3 Display| G[Show waiting queue]
    D -->|4 Search| H[Search by patient ID]
    D -->|5 Update| I[Update patient details]
    D -->|6 Cancel| J[Remove selected patient]
    D -->|7 Count| K[Show queue count]
    D -->|8 History| L[Read consultation history]
    D -->|9 Save| M[Write waiting records]
    D -->|10 Exit| N[Save records and exit]
    E --> C
    F --> O[Append consultation history]
    O --> C
    G --> C
    H --> C
    I --> C
    J --> C
    K --> C
    L --> C
    M --> C
    N --> P([End])
```

### 3. Add Patient: Enqueue

When a patient is added: 1. The program checks whether the queue has
reached its maximum capacity. 2. It reads and validates the patient ID.
3. It checks for a duplicate ID among patients currently waiting. 4. It
collects the patient's name, age, and problem. 5. It inserts the new
record at the rear of the circular queue. 6. It saves the updated
waiting list.

### 4. Call Next Patient: Dequeue

When the next patient is called: 1. The program checks whether the queue
is empty. 2. It copies the record at `front`. 3. It advances the `front`
index. 4. It decreases the waiting-patient count. 5. It appends the
consultation details and timestamp to the history file. 6. It saves the
updated waiting list.

### 5. Save and Load Records

  ----------------------------------------------------------------------------
  File                         Purpose                 Format
  ---------------------------- ----------------------- -----------------------
  `patients.dat`               Stores patients who are Binary
                               still waiting           

  `consultation_history.txt`   Stores the consultation Plain text
                               log                     
  ----------------------------------------------------------------------------

The waiting list is loaded when the application starts. The program
saves it after changes and when the user exits.

**Important:** These files are created in the program's current working
directory. Run the application from a folder where it has permission to
create and modify files.

## Technologies Used

-   **C** --- core programming language.
-   **Circular Queue** --- maintains the patient waiting order.
-   **Structures (`struct`)** --- groups each patient's ID, name, age,
    and problem.
-   **Functions** --- separates the program into manageable operations.
-   **File handling** --- uses standard C file functions such as
    `fopen`, `fread`, `fwrite`, `fprintf`, and `fgets`.
-   **GCC** --- compiler used to build the program.
-   **Visual Studio Code** --- recommended editor and development
    environment.

## Project Structure

``` text
HOSPITAL-PATIENT-MANAGEMENT-SYSTEM/
|
+-- src/
|   +-- hospital.c                 Main C source code
|
+-- include/                       Header files (if added)
+-- tests/                         Test cases (if added)
+-- docs/                          Project documentation
+-- screenshots/                   Application screenshots
|
+-- README.md                      Project documentation
+-- .gitignore                     Files excluded from Git
|
+-- hospital.exe                   Generated after compilation
+-- patients.dat                   Generated waiting-list data
+-- consultation_history.txt       Generated consultation log
```

`hospital.exe`, `patients.dat`, and `consultation_history.txt` are
generated during compilation or at runtime. They do not need to be
committed to GitHub.

## Installation and Setup

### Prerequisites

Install the following:

1.  [Visual Studio Code](https://code.visualstudio.com/)
2.  A C compiler such as [GCC](https://gcc.gnu.org/)
3.  Git (optional, for uploading the project to GitHub)

On Windows, GCC can be installed through
[MSYS2](https://www.msys2.org/). If using the MSYS2 UCRT64 environment,
make sure its `bin` directory is available in your PATH.

### Step 1: Clone the Repository

``` bash
git clone https://github.com/YOUR-USERNAME/HOSPITAL-PATIENT-MANAGEMENT-SYSTEM.git
```

Replace `YOUR-USERNAME` with your GitHub username.

Alternatively, download the repository as a ZIP file from GitHub and
extract it.

### Step 2: Open the Project

Open VS Code, select **File → Open Folder**, and choose the project
directory.

### Step 3: Compile

Open the integrated terminal in the project root.

**Windows PowerShell:**

``` powershell
gcc .\src\hospital.c -o .\hospital.exe -std=c11 -Wall -Wextra
```

If GCC is installed at the standard MSYS2 UCRT64 path:

``` powershell
& "C:\msys64\ucrt64\bin\gcc.exe" .\src\hospital.c -o .\hospital.exe -std=c11 -Wall -Wextra
```

**Linux or macOS:**

``` bash
gcc ./src/hospital.c -o hospital -std=c11 -Wall -Wextra
```

### Step 4: Run

**Windows PowerShell:**

``` powershell
.\hospital.exe
```

**Linux or macOS:**

``` bash
./hospital
```

If the compiler reports an error, check that the source file is located
at `src/hospital.c` and that GCC is installed correctly.

## How to Use

1.  Start the program.
2.  Enter a menu number from `1` to `10`.
3.  Choose **1** to add a patient. Enter an ID, name, age, and problem.
4.  Choose **3** to see the waiting list.
5.  Choose **4** to search for a patient by ID.
6.  Choose **5** to update a waiting patient's details.
7.  Choose **6** to cancel a patient who is still waiting.
8.  Choose **2** to call the next patient for consultation.
9.  Choose **8** to view the consultation history.
10. Choose **9** to save waiting records manually, or **10** to save and
    exit.

### Example Patient Record

``` text
Patient ID : 101
Name       : Rahul Kumar
Age        : 22
Problem    : Fever
```

## Suggested Test Cases

  -----------------------------------------------------------------------
  Test                    Action                  Expected result
  ----------------------- ----------------------- -----------------------
  1                       Display queue when      Show that no patients
                          empty                   are waiting.

  2                       Add a patient           Patient is added
                                                  successfully.

  3                       Add another patient     Duplicate ID is
                          with the same waiting   rejected.
                          ID                      

  4                       Add patients and        Patients appear in
                          display the queue       insertion order.

  5                       Call the next patient   The front patient is
                                                  removed and logged.

  6                       Search for an existing  Matching patient
                          waiting ID              details are displayed.

  7                       Search for a missing ID Patient-not-found
                                                  message is displayed.

  8                       Update a waiting        Updated details appear
                          patient                 in the queue.

  9                       Cancel a waiting        Selected patient is
                          patient                 removed; remaining
                                                  order is preserved.

  10                      Save, exit, and restart Saved waiting records
                                                  are loaded again, if
                                                  file access is
                                                  available.
  -----------------------------------------------------------------------

## Data Structure Operations and Complexity

Let **n** be the number of patients currently waiting.

  ------------------------------------------------------------------------
  Operation                          Time complexity Explanation
  --------------------- ---------------------------- ---------------------
  Enqueue / Add                                 O(n) Duplicate-ID check
                                                     scans the queue;
                                                     insertion itself is
                                                     O(1).

  Dequeue / Call next                           O(1) Removes the front
                                                     record and advances
                                                     the index.

  Display                                       O(n) Visits every waiting
                                                     patient.

  Search                                        O(n) May inspect every
                                                     patient.

  Update                                        O(n) Searches for the
                                                     patient before
                                                     updating.

  Cancel                                        O(n) Searches and shifts
                                                     subsequent queue
                                                     entries.

  Count                                         O(1) Uses the maintained
                                                     `count` variable.
  ------------------------------------------------------------------------

The queue has a fixed maximum capacity of **100 waiting patients**.

## Troubleshooting

### `gcc is not recognized`

GCC is either not installed or its `bin` directory is not in the system
PATH. Install GCC and configure PATH, or use the full MSYS2 GCC path
shown above.

### `hospital.exe` is not found

Check that compilation completed successfully and that the executable
was generated in the project root. Run it from that directory with
`.\hospital.exe`.

### `Could not save patient records`

The program could not open `patients.dat` for writing. Check that: - You
are running locally rather than in a restricted online compiler. - The
current working directory exists and is writable. - The file is not
blocked by permissions or another application.

Some online compilers do not support persistent file storage. Use a
local compiler for reliable save/load testing.

### Waiting records do not appear after restarting

Keep `patients.dat` in the same working directory from which the
application is launched. The program looks for that filename in its
current working directory.

## Future Enhancements

-   [ ] Doctor management and doctor-wise queues
-   [ ] Emergency patient priority
-   [ ] Appointment booking and scheduling
-   [ ] Patient billing and payment records
-   [ ] Admin login and role-based access
-   [ ] Patient discharge management
-   [ ] Searchable reports and statistics
-   [ ] Database integration
-   [ ] Graphical user interface

## Learning Outcomes

By developing this project, students can practise:

-   Implementing a circular queue using an array.
-   Using structures to organise related data.
-   Applying FIFO logic to a practical scenario.
-   Breaking a program into reusable functions.
-   Validating user input.
-   Reading and writing records using C file handling.
-   Compiling, testing, debugging, and documenting a C application.
-   Managing project files with Git and GitHub.

## Limitations and Disclaimer

This is a **single-user educational console application**, not a
production hospital information system.

-   It supports up to 100 waiting patients.
-   Duplicate IDs are checked only among patients currently waiting. An
    ID may be reused after that patient is called or cancelled.
-   Consultation history is stored as a simple text log.
-   The binary data file is intended for this program and is not a
    portable database format.
-   The application does not include production-grade authentication,
    encryption, audit controls, backups, or privacy safeguards.

**Do not enter real patient information.** This project is intended for
learning and demonstration only, and must not be used for clinical
decisions or real hospital operations.
