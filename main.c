#include <stdio.h>

#define MAX 100

struct Patient
{
    int id;
    char name[50];
    int age;
    char problem[100];
};

struct Patient queue[MAX];

int front = 0;
int rear = -1;
int count = 0;

void addPatient(void)
{
    struct Patient p;

    if (count == MAX)
    {
        printf("\nWaiting queue is full!\n");
        return;
    }

    printf("\nEnter Patient ID: ");
    if (scanf("%d", &p.id) != 1)
    {
        printf("Invalid Patient ID.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        int index = (front + i) % MAX;
        if (queue[index].id == p.id)
        {
            printf("Patient ID already exists!\n");
            return;
        }
    }

    printf("Enter Patient Name: ");
    scanf(" %49[^\n]", p.name);

    printf("Enter Patient Age: ");
    if (scanf("%d", &p.age) != 1 || p.age < 0)
    {
        printf("Invalid age.\n");
        return;
    }

    printf("Enter Patient Problem: ");
    scanf(" %99[^\n]", p.problem);

    rear = (rear + 1) % MAX;
    queue[rear] = p;
    count++;

    printf("\nPatient added successfully!\n");
}

void callPatient(void)
{
    if (count == 0)
    {
        printf("\nNo patients are waiting.\n");
        return;
    }

    printf("\nNext Patient for Consultation:\n");
    printf("Patient ID: %d\n", queue[front].id);
    printf("Name: %s\n", queue[front].name);
    printf("Age: %d\n", queue[front].age);
    printf("Problem: %s\n", queue[front].problem);
    printf("\nPatient called for consultation.\n");

    front = (front + 1) % MAX;
    count--;

    if (count == 0)
    {
        rear = front - 1;
    }
}

void displayPatients(void)
{
    if (count == 0)
    {
        printf("\nNo patients are waiting.\n");
        return;
    }

    printf("\n--- Waiting Patients ---\n");
    for (int i = 0; i < count; i++)
    {
        int index = (front + i) % MAX;
        printf("\nPatient ID: %d\n", queue[index].id);
        printf("Name: %s\n", queue[index].name);
        printf("Age: %d\n", queue[index].age);
        printf("Problem: %s\n", queue[index].problem);
    }
}

void searchPatient(void)
{
    int id, found = 0;

    printf("\nEnter Patient ID to search: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Invalid Patient ID.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        int index = (front + i) % MAX;
        if (queue[index].id == id)
        {
            printf("\nPatient Found!\n");
            printf("Patient ID: %d\n", queue[index].id);
            printf("Name: %s\n", queue[index].name);
            printf("Age: %d\n", queue[index].age);
            printf("Problem: %s\n", queue[index].problem);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nPatient not found in waiting queue.\n");
    }
}

void countPatients(void)
{
    printf("\nTotal patients waiting: %d\n", count);
}

int main(void)
{
    int choice;

    do
    {
        printf("\n===== HOSPITAL PATIENTS MANAGEMENT SYSTEM =====\n");
        printf("1. Add Patient\n");
        printf("2. Call Next Patient\n");
        printf("3. Display Waiting Patients\n");
        printf("4. Search Patient\n");
        printf("5. Count Waiting Patients\n");
        printf("6. Exit\n");
        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input. Please enter a number.\n");
            return 1;
        }

        switch (choice)
        {
            case 1:
                addPatient();
                break;
            case 2:
                callPatient();
                break;
            case 3:
                displayPatients();
                break;
            case 4:
                searchPatient();
                break;
            case 5:
                countPatients();
                break;
            case 6:
                printf("\nExiting the program.\n");
                break;
            default:
                printf("\nInvalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}
