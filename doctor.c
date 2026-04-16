#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doctor.h"
#include "patient.h"
#include "globals.h"
void addDoctor() {
    struct Doctor* newDoc = (struct Doctor*)malloc(sizeof(struct Doctor));
    if (!newDoc) return;
    newDoc->doctorID = ++doctorCounter;
    printf("Enter Doctor Name: ");
    scanf(" %[^\n]", newDoc->name);
    printf("Enter Specialisation: ");
    scanf(" %[^\n]", newDoc->specialisation);
    printf("Enter Contact: ");
    scanf(" %[^\n]", newDoc->contact);
    printf("Enter Availability: ");
    scanf(" %[^\n]", newDoc->availability);
    newDoc->patientHead = NULL;
    newDoc->patientTail = NULL;
    newDoc->next = NULL;
    if (doctorHead == NULL) {
        newDoc->prev = NULL;
        doctorHead = newDoc;
        doctorTail = newDoc;
    } else {
        newDoc->prev = doctorTail;
        doctorTail->next = newDoc;
        doctorTail = newDoc;
    }
    printf("Doctor added with ID: %d\n", newDoc->doctorID);
}
struct Doctor* searchDoctorByID(int doctorID) {
    struct Doctor* curr = doctorHead;
    while (curr != NULL) {
        if (curr->doctorID == doctorID) return curr;
        curr = curr->next;
    }
    return NULL;
}
void deleteDoctor(int doctorID) {
    struct Doctor* doc = searchDoctorByID(doctorID);
    if (doc == NULL) {
        printf("Doctor not found.\n");
        return;
    }
    struct Patient* currPat = doc->patientHead;
    while (currPat != NULL) {
        struct Patient* nextPat = currPat->next;
        free(currPat); // Freeing patients belonging to this doctor
        currPat = nextPat;
    }
    if (doc->prev != NULL) doc->prev->next = doc->next;
    else doctorHead = doc->next;
    if (doc->next != NULL) doc->next->prev = doc->prev;
    else doctorTail = doc->prev;
    free(doc);
    printf("Doctor and their patients deleted successfully.\n");
}
void displayAllDoctors() {
    struct Doctor* temp = doctorHead;
    printf("\n%-5s %-20s %-20s\n", "ID", "Name", "Specialisation");
    printf("--------------------------------------------------\n");
    while (temp != NULL) {
        printf("%-5d %-20s %-20s\n", temp->doctorID, temp->name, temp->specialisation);
        temp = temp->next;
    }
}