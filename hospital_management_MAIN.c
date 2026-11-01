/*
 * HOSPITAL PATIENT MANAGEMENT SYSTEM
 * Data structure: Circular Queue
 *
 * Features:
 * 1. Add patient (enqueue)
 * 2. Call next patient (dequeue)
 * 3. Display waiting patients
 * 4. Search patient by ID
 * 5. Update waiting-patient details
 * 6. Cancel/remove a patient by ID
 * 7. Count waiting patients
 * 8. View consultation history
 * 9. Save records
 * 10. Exit
 *
 * Waiting patients are saved in patients.dat.
 * Called patients are appended to consultation_history.txt.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define MAX 100
#define NAME_LEN 50
#define PROBLEM_LEN 100
#define DATA_FILE "patients.dat"
#define HISTORY_FILE "consultation_history.txt"

typedef struct
{
    int id;
    char name[NAME_LEN];
    int age;
    char problem[PROBLEM_LEN];
} Patient;

static Patient queue[MAX];
static int front = 0;
static int rear = -1;
static int count = 0;

/* Read a complete line safely, including spaces. */
static void readLine(const char *prompt, char *buffer, size_t size)
{
    int ch;
    size_t len;

    printf("%s", prompt);

    if (fgets(buffer, (int)size, stdin) == NULL)
    {
        buffer[0] = '\0';
        return;
    }

    len = strlen(buffer);

    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }
    else
    {
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
            /* Discard extra input. */
        }
    }
}

/* Read and validate an integer. */
static int readInt(const char *prompt, int minValue, int maxValue, int *value)
{
    char input[100];
    char *end;
    long number;

    for (;;)
    {
        readLine(prompt, input, sizeof(input));

        errno = 0;
        number = strtol(input, &end, 10);

        while (*end == ' ' || *end == '\t')
        {
            end++;
        }

        if (input[0] != '\0' && *end == '\0' &&
            errno == 0 && number >= minValue && number <= maxValue)
        {
            *value = (int)number;
            return 1;
        }

        printf("Invalid input. Enter a number from %d to %d.\n",
               minValue, maxValue);
    }
}

static int indexAt(int position)
{
    return (front + position) % MAX;
}

static int findPatientPosition(int id)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (queue[indexAt(i)].id == id)
        {
            return i;
        }
    }

    return -1;
}

/* Save waiting patients in their current FIFO order. */
static int saveQueue(void)
{
    FILE *file;
    int i;

    file = fopen(DATA_FILE, "wb");
    if (file == NULL)
    {
        printf("Warning: Could not save patient records.\n");
        return 0;
    }

    if (fwrite(&count, sizeof(count), 1, file) != 1)
    {
        fclose(file);
        printf("Warning: Error saving patient count.\n");
        return 0;
    }

    for (i = 0; i < count; i++)
    {
        if (fwrite(&queue[indexAt(i)], sizeof(Patient), 1, file) != 1)
        {
            fclose(file);
            printf("Warning: Error saving patient records.\n");
            return 0;
        }
    }

    fclose(file);
    return 1;
}

/* Load saved waiting patients when the program starts. */
static void loadQueue(void)
{
    FILE *file;
    int savedCount;
    int i;

    file = fopen(DATA_FILE, "rb");
    if (file == NULL)
    {
        return; /* First run: no saved file exists yet. */
    }

    if (fread(&savedCount, sizeof(savedCount), 1, file) != 1 ||
        savedCount < 0 || savedCount > MAX)
    {
        printf("Saved data is invalid. Starting with an empty queue.\n");
        fclose(file);
        return;
    }

    for (i = 0; i < savedCount; i++)
    {
        if (fread(&queue[i], sizeof(Patient), 1, file) != 1)
        {
            printf("Saved data is incomplete. Starting with an empty queue.\n");
            fclose(file);
            count = 0;
            front = 0;
            rear = -1;
            return;
        }

        queue[i].name[NAME_LEN - 1] = '\0';
        queue[i].problem[PROBLEM_LEN - 1] = '\0';
    }

    fclose(file);

    count = savedCount;
    front = 0;
    rear = count - 1;

    printf("%d waiting patient record(s) loaded.\n", count);
}

static void printPatient(const Patient *p)
{
    printf("\nPatient ID : %d\n", p->id);
    printf("Name       : %s\n", p->name);
    printf("Age        : %d\n", p->age);
    printf("Problem    : %s\n", p->problem);
}

static void addPatient(void)
{
    Patient p;

    if (count == MAX)
    {
        printf("\nWaiting queue is full. Cannot add more patients.\n");
        return;
    }

    readInt("\nEnter Patient ID: ", 1, 2147483647, &p.id);

    if (findPatientPosition(p.id) != -1)
    {
        printf("A patient with this ID is already waiting.\n");
        return;
    }

    do
    {
        readLine("Enter Patient Name: ", p.name, sizeof(p.name));
        if (p.name[0] == '\0')
        {
            printf("Name cannot be empty.\n");
        }
    } while (p.name[0] == '\0');

    readInt("Enter Patient Age (1-130): ", 1, 130, &p.age);

    do
    {
        readLine("Enter Patient Problem: ", p.problem, sizeof(p.problem));
        if (p.problem[0] == '\0')
        {
            printf("Problem cannot be empty.\n");
        }
    } while (p.problem[0] == '\0');

    rear = (rear + 1) % MAX;
    queue[rear] = p;
    count++;

    printf("\nPatient added successfully (ENQUEUE).\n");
    saveQueue();
}

/* POP/DEQUEUE: remove the patient at the front of the circular queue. */
static int popPatient(Patient *removedPatient)
{
    if (count == 0)
    {
        return 0;
    }

    *removedPatient = queue[front];
    front = (front + 1) % MAX;
    count--;

    if (count == 0)
    {
        front = 0;
        rear = -1;
    }

    return 1;
}

static void recordConsultation(const Patient *p)
{
    FILE *file;
    time_t now;
    struct tm *timeInfo;
    char timeText[30];

    now = time(NULL);
    timeInfo = localtime(&now);

    if (timeInfo != NULL &&
        strftime(timeText, sizeof(timeText), "%Y-%m-%d %H:%M:%S", timeInfo) > 0)
    {
        /* timeText contains the formatted date and time. */
    }
    else
    {
        strcpy(timeText, "Time unavailable");
    }

    file = fopen(HISTORY_FILE, "a");
    if (file == NULL)
    {
        printf("Warning: Could not write consultation history.\n");
        return;
    }

    fprintf(file,
            "Date/Time: %s | ID: %d | Name: %s | Age: %d | Problem: %s\n",
            timeText, p->id, p->name, p->age, p->problem);

    fclose(file);
}

static void callNextPatient(void)
{
    Patient p;

    if (!popPatient(&p))
    {
        printf("\nNo patients are waiting.\n");
        return;
    }

    printf("\nNEXT PATIENT FOR CONSULTATION\n");
    printPatient(&p);
    recordConsultation(&p);
    saveQueue();

    printf("\nPatient called and removed from the waiting queue.\n");
}

static void displayPatients(void)
{
    int i;

    if (count == 0)
    {
        printf("\nNo patients are waiting.\n");
        return;
    }

    printf("\n========== WAITING PATIENTS (%d) ==========\n", count);

    for (i = 0; i < count; i++)
    {
        printf("\nQueue position: %d", i + 1);
        printPatient(&queue[indexAt(i)]);
    }
}

static void searchPatient(void)
{
    int id;
    int position;

    readInt("\nEnter Patient ID to search: ", 1, 2147483647, &id);
    position = findPatientPosition(id);

    if (position == -1)
    {
        printf("\nPatient not found in the waiting queue.\n");
        return;
    }

    printf("\nPatient found at queue position %d.\n", position + 1);
    printPatient(&queue[indexAt(position)]);
}

static void updatePatient(void)
{
    int id;
    int position;
    Patient *p;

    readInt("\nEnter Patient ID to update: ", 1, 2147483647, &id);
    position = findPatientPosition(id);

    if (position == -1)
    {
        printf("\nPatient not found in the waiting queue.\n");
        return;
    }

    p = &queue[indexAt(position)];

    printf("\nCurrent patient details:\n");
    printPatient(p);

    printf("\nEnter updated details:\n");

    do
    {
        readLine("New Patient Name: ", p->name, sizeof(p->name));
        if (p->name[0] == '\0')
        {
            printf("Name cannot be empty.\n");
        }
    } while (p->name[0] == '\0');

    readInt("New Patient Age (1-130): ", 1, 130, &p->age);

    do
    {
        readLine("New Patient Problem: ", p->problem, sizeof(p->problem));
        if (p->problem[0] == '\0')
        {
            printf("Problem cannot be empty.\n");
        }
    } while (p->problem[0] == '\0');

    saveQueue();
    printf("\nPatient details updated successfully.\n");
}

/* Remove a patient from any queue position while preserving FIFO order. */
static void cancelPatient(void)
{
    int id;
    int position;
    int i;

    readInt("\nEnter Patient ID to cancel: ", 1, 2147483647, &id);
    position = findPatientPosition(id);

    if (position == -1)
    {
        printf("\nPatient not found in the waiting queue.\n");
        return;
    }

    for (i = position; i < count - 1; i++)
    {
        queue[indexAt(i)] = queue[indexAt(i + 1)];
    }

    count--;

    if (count == 0)
    {
        front = 0;
        rear = -1;
    }
    else
    {
        rear = indexAt(count - 1);
    }

    saveQueue();
    printf("\nPatient ID %d has been removed from the waiting queue.\n", id);
}

static void countPatients(void)
{
    printf("\nTotal patients waiting: %d / %d\n", count, MAX);
    printf("Available queue spaces: %d\n", MAX - count);
}

static void viewConsultationHistory(void)
{
    FILE *file;
    char line[300];
    int found = 0;

    file = fopen(HISTORY_FILE, "r");
    if (file == NULL)
    {
        printf("\nNo consultation history is available yet.\n");
        return;
    }

    printf("\n========== CONSULTATION HISTORY ==========\n");

    while (fgets(line, sizeof(line), file) != NULL)
    {
        fputs(line, stdout);
        found = 1;
    }

    if (!found)
    {
        printf("No consultation records found.\n");
    }

    fclose(file);
}

static void showMenu(void)
{
    printf("\n============================================\n");
    printf("       HOSPITAL PATIENT MANAGEMENT SYSTEM\n");
    printf("============================================\n");
    printf("1.  Add Patient (Enqueue)\n");
    printf("2.  Call Next Patient (Pop / Dequeue)\n");
    printf("3.  Display Waiting Patients\n");
    printf("4.  Search Patient\n");
    printf("5.  Update Patient Details\n");
    printf("6.  Cancel Patient from Queue\n");
    printf("7.  Count Waiting Patients\n");
    printf("8.  View Consultation History\n");
    printf("9.  Save Patient Records\n");
    printf("10. Exit\n");
}

int main(void)
{
    int choice;

    loadQueue();

    do
    {
        showMenu();
        readInt("\nEnter your choice: ", 1, 10, &choice);

        switch (choice)
        {
            case 1:
                addPatient();
                break;
            case 2:
                callNextPatient();
                break;
            case 3:
                displayPatients();
                break;
            case 4:
                searchPatient();
                break;
            case 5:
                updatePatient();
                break;
            case 6:
                cancelPatient();
                break;
            case 7:
                countPatients();
                break;
            case 8:
                viewConsultationHistory();
                break;
            case 9:
                if (saveQueue())
                {
                    printf("\nWaiting patient records saved successfully.\n");
                }
                break;
            case 10:
                saveQueue();
                printf("\nRecords saved. Exiting the program. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice.\n");
        }

    } while (choice != 10);

    return 0;
}
