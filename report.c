#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doctor.h"
#include "patient.h"
#include "billing.h"
#include "appointment.h"
#include "globals.h"

void patientReport(int patientID) {
    /* FIX: search_Patient() does not exist anywhere in the project.
       Replaced with searchPatientByID() which is the correct silent lookup. */
    struct Patient* pat = searchPatientByID(patientID);
    if (pat == NULL) {
        printf("Patient not found\n");
        return;
    }
    printf("\n========== PATIENT REPORT ==========\n");
    printf("Patient ID  : %d\n", pat->PatientID);
    printf("Name        : %s\n", pat->name);
    printf("Gender      : %s\n", pat->gender);
    printf("Age         : %d\n", pat->age);
    if (pat->Doctor != NULL) {
        printf("Doctor      : %s\n", pat->Doctor->name);
    }

    printf("\n--- Appointments ---\n");
    printf("%-8s %-12s %-10s %-10s\n", "Appt ID", "Date", "Time", "Status");
    printf("--------------------------------------------\n");
    struct Appointment* app = appointmentHead;
    while (app != NULL) {
        if (app->patientPtr != NULL && app->patientPtr->PatientID == pat->PatientID) {
            printf("%-8d %-12s %-10s %-10s\n",
                   app->appointmentID, app->date, app->time, app->status);
        }
        app = app->next;
    }

    printf("\n--- Bills ---\n");
    printf("%-8s %-30s %-12s %-10s\n", "Bill ID", "Services", "Amount", "Status");
    printf("------------------------------------------------------------\n");
    struct Bill* bill = billHead;
    while (bill != NULL) {
        if (bill->patientPtr != NULL && bill->patientPtr->PatientID == pat->PatientID) {
            printf("%-8d %-30s $%-11.2f %-10s\n",
                   bill->billID, bill->services,
                   bill->totalAmount, bill->paymentStatus);
        }
        bill = bill->next;
    }
}

void doctorWorkloadReport(int doctorID) {
    struct Doctor* doctor = searchDoctorByID(doctorID);
    if (doctor == NULL) {
        printf("Doctor not found\n");
        return;
    }
    int patcount = 0;
    int appcount = 0;

    printf("\n========== DOCTOR WORKLOAD REPORT ==========\n");
    printf("Doctor: %s (ID: %d)\n", doctor->name, doctor->doctorID);

    /* FIX: Original code iterated doctor->patientHead which is ALWAYS NULL because
       patients are stored only in the global list (patientHead), never linked
       per-doctor. Now we scan the global patient list and filter by doctor. */
    printf("\n--- Assigned Patients ---\n");
    struct Patient* pat = patientHead;
    while (pat != NULL) {
        if (pat->Doctor != NULL && pat->Doctor->doctorID == doctorID) {
            printf("  Patient ID: %-5d Name: %s\n", pat->PatientID, pat->name);
            patcount++;
        }
        pat = pat->next;
    }

    printf("\n--- Appointments ---\n");
    printf("%-8s %-12s %-10s %-10s\n", "Appt ID", "Date", "Time", "Status");
    printf("--------------------------------------------\n");
    struct Appointment* app = appointmentHead;
    while (app != NULL) {
        if (app->doctorPtr != NULL && app->doctorPtr->doctorID == doctorID) {
            printf("%-8d %-12s %-10s %-10s\n",
                   app->appointmentID, app->date, app->time, app->status);
            appcount++;
        }
        app = app->next;
    }

    printf("\nTotal patients : %d\n", patcount);
    printf("Total appointments: %d\n", appcount);
}

void revenueReport() {
    float paidTotal   = 0.0f;
    float unpaidTotal = 0.0f;
    struct Bill* bill = billHead;
    while (bill != NULL) {
        /* Note: paymentStatus is saved as "Unpaid" by default. When a payment
           feature is added, use the same casing here. Currently "Paid" vs "Unpaid". */
        if (strcmp(bill->paymentStatus, "Paid") == 0) {
            paidTotal += bill->totalAmount;
        } else {
            unpaidTotal += bill->totalAmount;
        }
        bill = bill->next;
    }
    float grandTotal = paidTotal + unpaidTotal;
    printf("\n========== REVENUE REPORT ==========\n");
    printf("Paid total   : $%.2f\n", paidTotal);
    printf("Unpaid total : $%.2f\n", unpaidTotal);
    printf("Grand total  : $%.2f\n", grandTotal);
}
