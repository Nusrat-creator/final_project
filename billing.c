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

    //xesteden ogurlanan pullar:
    float priceConsultation = 50.00;
    float priceBloodWork = 30.00;
    float priceXRay = 100.00;
    float priceMedication = 45.50;
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
    printf("\nSuccess! Total Amount Calculated: $%.2f\n", newBill->totalAmount);
    printf("Bill ID assigned: %d\n", newBill->billID);
}