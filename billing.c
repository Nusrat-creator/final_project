#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "billing.h"
#include "appointment.h"
#include "patient.h"
#include "globals.h"

void generateBill(int appointmentID) {
    struct Appointment* appt = searchAppointmentByID(appointmentID);
    if (appt == NULL) {
        printf("Error: Appointment ID %d not found.\n", appointmentID);
        return;
    }
    struct Bill* newBill = (struct Bill*)malloc(sizeof(struct Bill));
    if (newBill == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }
    newBill->billID = ++billCounter;
    newBill->appointmentPtr = appt;
    newBill->patientPtr = appt->patientPtr;
    newBill->totalAmount = 0.0f;
    strcpy(newBill->services, "");
    strcpy(newBill->paymentStatus, "Unpaid");

    float priceConsultation = 50.00f;
    float priceBloodWork    = 30.00f;
    float priceXRay         = 100.00f;
    float priceMedication   = 45.50f;
    int choice;

    printf("\n--- Generating Bill for Appt %d (Patient: %s) ---\n",
           appointmentID, appt->patientPtr->name);
    while (1) {
        printf("\nSelect Services provided:\n");
        printf("1. Consultation ($%.2f)\n", priceConsultation);
        printf("2. Blood Work   ($%.2f)\n", priceBloodWork);
        printf("3. X-Ray        ($%.2f)\n", priceXRay);
        printf("4. Medication   ($%.2f)\n", priceMedication);
        printf("0. Done (Generate Total)\n");
        printf("Choice: ");
        scanf("%d", &choice);
        if (choice == 0) break;
        switch (choice) {
            case 1:
                newBill->totalAmount += priceConsultation;
                strcat(newBill->services, "Consultation; ");
                break;
            case 2:
                newBill->totalAmount += priceBloodWork;
                strcat(newBill->services, "Blood Work; ");
                break;
            case 3:
                newBill->totalAmount += priceXRay;
                strcat(newBill->services, "X-Ray; ");
                break;
            case 4:
                newBill->totalAmount += priceMedication;
                strcat(newBill->services, "Medication; ");
                break;
            default:
                printf("Invalid selection.\n");
        }
    }
    newBill->next = NULL;
    if (billHead == NULL) {
        newBill->prev = NULL;
        billHead = newBill;
        billTail = newBill;
    } else {
        newBill->prev = billTail;
        billTail->next = newBill;
        billTail = newBill;
    }
    printf("\nBill ID: %d | Total: $%.2f | Status: %s\n",
           newBill->billID, newBill->totalAmount, newBill->paymentStatus);
}

/* FIX: savebillings and loadbillings were declared in billing.h but never
   implemented — caused linker errors (undefined reference). */
void savebillings() {
    FILE *f = fopen("bills.txt", "w");
    if (!f) return;
    struct Bill* curr = billHead;
    while (curr) {
        int pID = (curr->patientPtr)     ? curr->patientPtr->PatientID       : -1;
        int aID = (curr->appointmentPtr) ? curr->appointmentPtr->appointmentID : -1;
        fprintf(f, "%d|%d|%d|%s|%.2f|%s\n",
                curr->billID, pID, aID,
                curr->services, curr->totalAmount, curr->paymentStatus);
        curr = curr->next;
    }
    fclose(f);
}

void loadbillings() {
    FILE *f = fopen("bills.txt", "r");
    if (!f) return;
    while (1) {
        struct Bill* b = malloc(sizeof(struct Bill));
        if (!b) break;
        int pID, aID;
        if (fscanf(f, "%d|%d|%d|%499[^|]|%f|%19[^\n]\n",
            &b->billID, &pID, &aID,
            b->services, &b->totalAmount, b->paymentStatus) != 6) {
            free(b);
            break;
        }
        b->patientPtr     = searchPatientByID(pID);
        b->appointmentPtr = searchAppointmentByID(aID);
        b->next = NULL;
        if (!billHead) { b->prev = NULL; billHead = b; billTail = b; }
        else { b->prev = billTail; billTail->next = b; billTail = b; }
        if (b->billID > billCounter) billCounter = b->billID;
    }
    fclose(f);
}
