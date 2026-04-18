//
// Created by ufaz on 4/18/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doctor.h"
#include "patient.h"
#include "globals.h"
void register_Patient() {
    int doc_id;
    struct Patient* newPat = (struct Patient*)malloc(sizeof(struct Patient));
    if (!newPat) return;
    newPat->PatientID = ++patientCounter;
    printf("Enter Patient Name: ");
    scanf(" %[^\n]", newPat->name);
    printf("Enter Age: ");
    scanf("%d", &newPat->age);
    printf("Enter Gender: ");
    scanf("%s", newPat->gender);
    printf("Enter Contact: ");
    scanf(" %[^\n]", newPat->contact);
    printf("Enter medical history: ");
    scanf(" %[^\n]", newPat->medical_history);
    printf("Enter Doctor's ID: ");
    scanf("%d", &doc_id);
    while (searchDoctorByID(doc_id) == NULL) {
        printf("Doctor does not exist!Please write a correct id!\n");
        scanf("%d", &doc_id);
    }
    newPat->Doctor = searchDoctorByID(doc_id);
    newPat->next = NULL;

    if (patientHead == NULL) {
        newPat->prev = NULL;
        patientHead = newPat;
        patientTail = newPat;
    } else {
        newPat->prev = patientTail;
        patientTail->next = newPat;
        patientTail = newPat;
    }
    printf("Patient registered with ID: %d\n", newPat->PatientID);
}
struct Patient* search_Patient(int PatientID) {
    struct Patient* curr = patientHead;
    while (curr != NULL) {
        if (curr->PatientID == PatientID) return curr;
        curr = curr->next;
    }
    return NULL;

}
struct Patient* retrieve_patient(int PatientID) {
    struct Patient* patient;
    patient = search_Patient(PatientID);
    if (patient == NULL) {return NULL;}
    printf("All information about Patient:\n");
    printf("Name: %s Age: %d Contact: %s Medical History: %s Gender: %s ", patient->name,patient->age,patient->contact,patient->medical_history,patient->gender);
    if (patient->Doctor != NULL) {
        printf("Assigned Doctor's ID and Name:%d,%s",patient->Doctor->doctorID,patient->Doctor->name);
    }
    return patient;

}

void update_Patient(int PatientID) {
    char info;
    int doc_id;
    struct Patient* patient= search_Patient(PatientID);
    if (patient == NULL) {printf("Patient does not exist\n"); return;}
    printf("What detail do you want to update?Age,Gender,Contact,Medical History,name,assigned doctor(with id)?(a/g/c/m/n/d)\n");
    scanf(" %c", &info);
    switch (info) {
        case 'a':
            scanf(" %d", &patient->age);
            printf("Age is now %d\n", patient->age);
            break;
        case 'g':
            scanf(" %[^\n]", patient->gender);
            printf("Gender is now %s\n", patient->gender);
            break;
        case 'c':
            scanf(" %[^\n]", patient->contact);
            printf("Contact is now %s\n", patient->contact);
            break;
        case 'm':
            scanf(" %[^\n]", patient->medical_history);
            printf("Medical history is now %s\n", patient->medical_history);
            break;
        case 'n':
            scanf(" %[^\n]", patient->name);
            printf("Name is now %s\n", patient->name);
            break;

        case 'd':
            scanf("%d", &doc_id);
            if (searchDoctorByID(doc_id) != NULL ) {
                patient->Doctor = searchDoctorByID(doc_id);
            }
            else {
                printf("Doctor does not exist\n");
            }
            break;


        default:
            printf("User didn't write requested thing,change declined");
            break;

        }
    }
void delete_Patient(int PatientID) {
    struct Patient* patient = search_Patient(PatientID);
    if (patient == NULL) {
        printf("Patient not found.\n");
        return;
    }
    if (patient->prev != NULL) patient->prev->next = patient->next;
    else patientHead = patient->next;
    if (patient->next != NULL) patient->next->prev = patient->prev;
    else patientTail = patient->prev;
    free(patient);
    printf("Patient is deleted successfully.\n");
}









