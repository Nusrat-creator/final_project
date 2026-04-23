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
    /* FIX: Original code tried to free from doc->patientHead, but patients are
       stored in the GLOBAL list — doc->patientHead is always NULL.
       Now we unlink patients from the global list and nullify their doctor pointer. */
    struct Patient* curr = patientHead;
    while (curr != NULL) {
        struct Patient* next = curr->next;
        if (curr->Doctor != NULL && curr->Doctor->doctorID == doctorID) {
            curr->Doctor = NULL; /* Detach so they're not left with a dangling pointer */
        }
        curr = next;
    }

    if (doc->prev != NULL) doc->prev->next = doc->next;
    else doctorHead = doc->next;
    if (doc->next != NULL) doc->next->prev = doc->prev;
    else doctorTail = doc->prev;
    free(doc);
    printf("Doctor deleted successfully. Their patients remain but are now unassigned.\n");
}

void updateDoctor(int doctorID) {
    struct Doctor* doc = searchDoctorByID(doctorID);
    if (doc == NULL) {
        printf("Doctor ID %d not found.\n", doctorID);
        return;
    }
    printf("\n--- Updating Doctor: %s (ID: %d) ---\n", doc->name, doc->doctorID);
    printf("What would you like to update?\n");
    printf("1. Name\n");
    printf("2. Specialisation\n");
    printf("3. Contact\n");
    printf("4. Availability\n");
    printf("Choice: ");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("Enter new name: ");
            scanf(" %[^\n]", doc->name);
            printf("Name updated to: %s\n", doc->name);
            break;
        case 2:
            printf("Enter new specialisation: ");
            scanf(" %[^\n]", doc->specialisation);
            printf("Specialisation updated to: %s\n", doc->specialisation);
            break;
        case 3:
            printf("Enter new contact: ");
            scanf(" %[^\n]", doc->contact);
            printf("Contact updated to: %s\n", doc->contact);
            break;
        case 4:
            printf("Enter new availability: ");
            scanf(" %[^\n]", doc->availability);
            printf("Availability updated to: %s\n", doc->availability);
            break;
        default:
            printf("Invalid choice — no changes made.\n");
            break;
    }
}

void searchDoctorByName(char* name) {
    struct Doctor* curr = doctorHead;
    int found = 0;
    printf("\n--- Search Results for Name: \"%s\" ---\n", name);
    while (curr != NULL) {
        /* strstr for partial/case match so "Ali" finds "Dr. Ali Hassan" */
        if (strstr(curr->name, name) != NULL) {
            printf("ID: %-5d | Name: %-20s | Specialisation: %-20s | Contact: %-15s | Availability: %s\n",
                   curr->doctorID, curr->name, curr->specialisation,
                   curr->contact, curr->availability);
            found++;
        }
        curr = curr->next;
    }
    if (found == 0) printf("No doctors found matching \"%s\".\n", name);
    else printf("%d result(s) found.\n", found);
}

void searchDoctorBySpecialisation(char* spec) {
    struct Doctor* curr = doctorHead;
    int found = 0;
    printf("\n--- Search Results for Specialisation: \"%s\" ---\n", spec);
    while (curr != NULL) {
        /* strstr so "Cardio" matches "Cardiology" */
        if (strstr(curr->specialisation, spec) != NULL) {
            printf("ID: %-5d | Name: %-20s | Specialisation: %-20s | Contact: %-15s | Availability: %s\n",
                   curr->doctorID, curr->name, curr->specialisation,
                   curr->contact, curr->availability);
            found++;
        }
        curr = curr->next;
    }
    if (found == 0) printf("No doctors found with specialisation \"%s\".\n", spec);
    else printf("%d result(s) found.\n", found);
}

void displayAllDoctors() {
    if (doctorHead == NULL) {
        printf("No doctors registered.\n");
        return;
    }
    struct Doctor* temp = doctorHead;
    printf("\n%-5s %-20s %-20s %-15s %-20s %-8s\n",
           "ID", "Name", "Specialisation", "Contact", "Availability", "Patients");
    printf("--------------------------------------------------------------------------------\n");
    while (temp != NULL) {
        /* Count this doctor's patients from the global list (per PDF spec: also
           print how many patients each doctor currently has). */
        int patCount = 0;
        struct Patient* p = patientHead;
        while (p != NULL) {
            if (p->Doctor != NULL && p->Doctor->doctorID == temp->doctorID)
                patCount++;
            p = p->next;
        }
        printf("%-5d %-20s %-20s %-15s %-20s %-8d\n",
               temp->doctorID, temp->name, temp->specialisation,
               temp->contact, temp->availability, patCount);
        temp = temp->next;
    }
    printf("--------------------------------------------------------------------------------\n");
}

void saveDoctors() {
    FILE *f = fopen("doctors.txt", "w");
    if (!f) return;
    struct Doctor* curr = doctorHead;
    while (curr) {
        fprintf(f, "%d|%s|%s|%s|%s\n",
                curr->doctorID, curr->name, curr->specialisation,
                curr->contact, curr->availability);
        curr = curr->next;
    }
    fclose(f);
}

void loadDoctors() {
    FILE *f = fopen("doctors.txt", "r");
    if (!f) return;
    /* FIX: Replaced while(!feof()) — reads last record twice. */
    while (1) {
        struct Doctor* d = malloc(sizeof(struct Doctor));
        if (!d) break;
        if (fscanf(f, "%d|%99[^|]|%99[^|]|%14[^|]|%19[^\n]\n",
            &d->doctorID, d->name, d->specialisation, d->contact, d->availability) != 5) {
            free(d);
            break;
        }
        d->next = NULL;
        d->patientHead = d->patientTail = NULL;
        if (!doctorHead) { d->prev = NULL; doctorHead = d; doctorTail = d; }
        else { d->prev = doctorTail; doctorTail->next = d; doctorTail = d; }
        if (d->doctorID > doctorCounter) doctorCounter = d->doctorID;
    }
    fclose(f);
}
