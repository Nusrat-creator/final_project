#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "doctor.h"
#include "patient.h"
#include "appointment.h"
#include  "billing.h"
void displayMenu() {
    printf("\n=========================================\n");
    printf("       HOSPITAL MANAGEMENT SYSTEM        \n");
    printf("=========================================\n");
    printf("1. Add a New Doctor\n");
    printf("2. Display All Doctors\n");
    printf("3. Register a New Patient\n");
    printf("4. Display/Retrieve a Patient\n");
    printf("5. Schedule an Appointment\n");
    printf("6. Display All Appointments\n");
    printf("7. Delete an Appointment\n");
    printf("0. Save and Exit\n");
    printf("=========================================\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    int tempID;

    printf("Booting up Hospital System...\n");

    loadDoctors();
    loadPatients();
    loadAppointments();

    printf("Data Loaded Successfully.\n");

    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            // Clears the buffer if the user types a letter instead of a number
            while(getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                addDoctor();
                break;
            case 2:
                displayAllDoctors();
                break;
            case 3:
                registerPatient();
                break;
            case 4:
                printf("Enter Patient ID to retrieve: ");
                scanf("%d", &tempID);
                // Call your search/retrieve function (Note: it prints info inside the function)
                struct Patient* p = retrieve_patient(tempID);
                if (p == NULL) {
                    printf("Patient not found.\n");
                }
                break;
            case 5:
                printf("Enter Patient ID to schedule appointment: ");
                scanf("%d", &tempID);
                addAppointment(tempID);
                break;
            case 6:
                displayAllAppointments();
                break;
            case 7:
                printf("Enter Appointment ID to delete: ");
                scanf("%d", &tempID);
                deleteAppointment(tempID);
                break;
            case 0:
                printf("\nInitiating Shutdown Sequence...\n");

                saveDoctors();
                savePatients();
                saveAppointments();

                printf("All data saved to files. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}