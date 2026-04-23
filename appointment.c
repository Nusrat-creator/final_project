#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "appointment.h"
#include "patient.h"
#include "doctor.h"
#include "globals.h"

void addAppointment(int patientID) {
    /* FIX: Use silent searchPatientByID so we don't print patient info here. */
    struct Patient* pat = searchPatientByID(patientID);
    if (pat == NULL) {
        printf("Error: Patient ID %d not found.\n", patientID);
        return;
    }
    struct Appointment* newAppt = (struct Appointment*)malloc(sizeof(struct Appointment));
    if (newAppt == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }
    newAppt->appointmentID = ++appointmentCounter;
    newAppt->patientPtr = pat;
    newAppt->doctorPtr = pat->Doctor;

    printf("\n--- Scheduling Appointment for Patient: %s ---\n", pat->name);
    printf("Enter Date (DD/MM/YYYY): ");
    scanf(" %[^\n]", newAppt->date);
    printf("Enter Time (HH:MM): ");
    scanf(" %[^\n]", newAppt->time);

    strcpy(newAppt->status, "Scheduled");
    newAppt->next = NULL;
    if (appointmentHead == NULL) {
        newAppt->prev = NULL;
        appointmentHead = newAppt;
        appointmentTail = newAppt;
    } else {
        newAppt->prev = appointmentTail;
        appointmentTail->next = newAppt;
        appointmentTail = newAppt;
    }
    printf("Appointment scheduled successfully. Appt ID: %d\n", newAppt->appointmentID);
}

struct Appointment* searchAppointmentByID(int appointmentID) {
    struct Appointment* current = appointmentHead;
    while (current != NULL) {
        if (current->appointmentID == appointmentID) return current;
        current = current->next;
    }
    return NULL;
}

void deleteAppointment(int appointmentID) {
    struct Appointment* appt = searchAppointmentByID(appointmentID);
    if (appt == NULL) {
        printf("Error: Appointment ID %d not found.\n", appointmentID);
        return;
    }
    if (appt->prev != NULL) appt->prev->next = appt->next;
    else appointmentHead = appt->next;
    if (appt->next != NULL) appt->next->prev = appt->prev;
    else appointmentTail = appt->prev;
    free(appt);
    printf("Appointment ID %d deleted successfully.\n", appointmentID);
}

void displayAllAppointments() {
    if (appointmentHead == NULL) {
        printf("No appointments scheduled.\n");
        return;
    }
    struct Appointment* current = appointmentHead;
    printf("\n----------------------------------------------------------------------\n");
    printf("%-8s %-15s %-15s %-12s %-10s %-10s\n",
           "Appt ID", "Patient Name", "Doctor Name", "Date", "Time", "Status");
    printf("----------------------------------------------------------------------\n");
    while (current != NULL) {
        printf("%-8d %-15s %-15s %-12s %-10s %-10s\n",
               current->appointmentID,
               current->patientPtr ? current->patientPtr->name : "N/A",
               current->doctorPtr  ? current->doctorPtr->name  : "N/A",
               current->date, current->time, current->status);
        current = current->next;
    }
    printf("----------------------------------------------------------------------\n");
}

void saveAppointments() {
    FILE *f = fopen("appointments.txt", "w");
    if (!f) return;
    struct Appointment* curr = appointmentHead;
    while (curr) {
        int pID = (curr->patientPtr) ? curr->patientPtr->PatientID : -1;
        int dID = (curr->doctorPtr)  ? curr->doctorPtr->doctorID   : -1;
        fprintf(f, "%d|%d|%d|%s|%s|%s\n",
                curr->appointmentID, pID, dID,
                curr->date, curr->time, curr->status);
        curr = curr->next;
    }
    fclose(f);
}

void loadAppointments() {
    FILE *f = fopen("appointments.txt", "r");
    if (!f) return;
    /* FIX: Replaced while(!feof()) — reads last record twice. */
    while (1) {
        struct Appointment* a = malloc(sizeof(struct Appointment));
        if (!a) break;
        int pID, dID;
        if (fscanf(f, "%d|%d|%d|%14[^|]|%9[^|]|%19[^\n]\n",
            &a->appointmentID, &pID, &dID,
            a->date, a->time, a->status) != 6) {
            free(a);
            break;
        }
        a->patientPtr = searchPatientByID(pID);
        a->doctorPtr  = searchDoctorByID(dID);
        a->next = NULL;
        if (!appointmentHead) { a->prev = NULL; appointmentHead = a; appointmentTail = a; }
        else { a->prev = appointmentTail; appointmentTail->next = a; appointmentTail = a; }
        if (a->appointmentID > appointmentCounter) appointmentCounter = a->appointmentID;
    }
    fclose(f);
}
