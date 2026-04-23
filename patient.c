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
        printf("Doctor does not exist! Please enter a correct ID: ");
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

/* FIX: New silent search — just finds and returns the pointer without printing.
   Used internally and by report.c to avoid double-printing patient info. */
struct Patient* searchPatientByID(int PatientID) {
    struct Patient* patient = patientHead;
    while (patient != NULL) {
        if (patient->PatientID == PatientID) return patient;
        patient = patient->next;
    }
    return NULL;
}

/* retrieve_patient now delegates finding to searchPatientByID, then prints. */
struct Patient* retrieve_patient(int PatientID) {
    struct Patient* patient = searchPatientByID(PatientID);
    if (patient != NULL) {
        printf("\nAll information about Patient:\n");
        printf("Name: %s | Age: %d | Contact: %s | Medical History: %s | Gender: %s\n",
               patient->name, patient->age, patient->contact,
               patient->medical_history, patient->gender);
        if (patient->Doctor != NULL) {
            printf("Assigned Doctor ID: %d, Name: %s\n",
                   patient->Doctor->doctorID, patient->Doctor->name);
        }
    }
    return patient;
}

void update_Patient(int PatientID) {
    char info;
    int doc_id;
    /* FIX: Use silent searchPatientByID so we don't print patient info on update. */
    struct Patient* patient = searchPatientByID(PatientID);
    if (patient == NULL) { printf("Patient does not exist\n"); return; }
    printf("What detail do you want to update? Age/Gender/Contact/Medical History/Name/Doctor (a/g/c/m/n/d): ");
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
            if (searchDoctorByID(doc_id) != NULL) {
                patient->Doctor = searchDoctorByID(doc_id);
                printf("Doctor updated.\n");
            } else {
                printf("Doctor does not exist.\n");
            }
            break;
        default:
            printf("Invalid option — change declined.\n");
            break;
    }
}

void savePatients() {
    FILE *f = fopen("patients.txt", "w");
    if (!f) return;
    struct Patient* curr = patientHead;
    while (curr) {
        int docID = (curr->Doctor) ? curr->Doctor->doctorID : -1;
        fprintf(f, "%d|%s|%d|%s|%s|%s|%d\n",
                curr->PatientID, curr->name, curr->age, curr->gender,
                curr->contact, curr->medical_history, docID);
        curr = curr->next;
    }
    fclose(f);
}

void loadPatients() {
    FILE *f = fopen("patients.txt", "r");
    if (!f) return;
    /* FIX: Replaced while(!feof()) — that pattern reads the last record twice.
       Now we allocate inside the loop and break when fscanf doesn't match. */
    while (1) {
        struct Patient* p = malloc(sizeof(struct Patient));
        if (!p) break;
        int docID;
        if (fscanf(f, "%d|%19[^|]|%d|%9[^|]|%99[^|]|%99[^|]|%d\n",
            &p->PatientID, p->name, &p->age, p->gender,
            p->contact, p->medical_history, &docID) != 7) {
            free(p);
            break;
        }
        p->Doctor = searchDoctorByID(docID);
        p->next = NULL;
        if (!patientHead) { p->prev = NULL; patientHead = p; patientTail = p; }
        else { p->prev = patientTail; patientTail->next = p; patientTail = p; }
        if (p->PatientID > patientCounter) patientCounter = p->PatientID;
    }
    fclose(f);
}
