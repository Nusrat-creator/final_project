//
// Created by ufaz on 4/22/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doctor.h"
#include "patient.h"
#include "billing.h"
#include "appointment.h"
#include "globals.h"

void patientReport(int patientID) {
    struct Patient* pat = search_Patient(patientID);
    if (pat ==NULL) {
        printf("Patient not found\n");
        return;
    }
    printf("\nPatient ID is: %d\n",pat->PatientID);
    printf("\nPatient Name is: %s\n",pat->name);
    printf("\nPatient Gender is: %s\n",pat->gender);
    printf("\nPatient Age is: %d\n",pat->age);
    if (pat->Doctor != NULL) {
        printf("\nDoctor is: %s\n",pat->Doctor->name);
    }
    struct Appointment* app = appointmentHead;
    printf("%-8s   %-12s %-10s %-10s\n",
           "Appt ID", "Date", "Time", "Status");
    printf("----------------------------------------------------------------------\n");
    while (app != NULL) {
        if (app->patientPtr->PatientID ==  pat->PatientID) {
            printf("%-8d %-12s %-10s %-10s\n",
               app->appointmentID,
               app->date,
               app->time,
               app->status);
        }
        app = app->next;
    }
    struct Bill* bill = billHead;
    printf("%-8s %-15s %-12s %-10s\n",
           "Bill ID", "Service", "Amount", "Status");
    printf("----------------------------------------------------------------------\n");
    while (bill != NULL) {
        if (bill->patientPtr->PatientID ==  pat->PatientID) {
            printf("%-8d %-15s %-12f %-10s\n",
               bill->billID,
               bill->services,
               bill->totalAmount,
               bill->paymentStatus);
        }
        bill = bill->next;
    }
}
void doctorWorkloadReport(int doctorID) {
    struct Doctor* doctor = searchDoctorByID(doctorID);
    int patcount = 0;
    int appcount = 0;
    if (doctor == NULL) {
        printf("Doctor not found\n");
        return;
    }
    struct Patient* pat = doctor->patientHead;
    while (pat != NULL) {
        printf("\nPatient Name is: %s\n",pat->name);
        patcount++;
        pat = pat->next;
    }
    struct Appointment* app = appointmentHead;
    printf("%-8s   %-12s %-10s %-10s\n",
           "Appt ID", "Date", "Time", "Status");
    printf("----------------------------------------------------------------------\n");
    while (app != NULL) {
        if (app->doctorPtr->doctorID ==  doctor->doctorID) {
            printf("%-8d %-12s %-10s %-10s\n",
               app->appointmentID,
               app->date,
               app->time,
               app->status);
        }
        appcount++;
        app = app->next;
    }
    printf("Number of patient doctors found: %d\n", patcount);
    printf("Number of appointments found: %d\n", appcount);
}
void revenueReport() {
    float paidTotal = 0.0;
    float unpaidTotal = 0.0;
    struct Bill* bill = billHead;
    while (bill != NULL) {
        if (strcmp(bill->paymentStatus,"paid") == 0) {
            paidTotal += bill->totalAmount;
        } else {
            unpaidTotal += bill->totalAmount;
        }
        bill = bill->next;
    }
    float grandTotal = paidTotal + unpaidTotal;
    printf("Paid total is: %f\n",paidTotal);
    printf("Unpaid total is: %f\n",unpaidTotal);
    printf("Grand total is: %f\n",grandTotal);

}





