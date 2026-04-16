//
// Created by seyid on 4/14/2026.
//
#ifndef SAP_FINAL_DOCTOR_H
#define SAP_FINAL_DOCTOR_H
struct Patient;
struct Doctor {
    int doctorID;
    char name[100];
    char specialisation[100];
    char contact[15];
    char availability[20];
    struct Patient* patientHead;
    struct Patient* patientTail;
    struct Doctor* prev;
    struct Doctor* next;
};
void addDoctor();
void deleteDoctor(int doctorID);
void updateDoctor(int doctorID);
struct Doctor* searchDoctorByID(int doctorID);
void searchDoctorByName(char* name);
void searchDoctorBySpecialisation(char* spec);
void displayAllDoctors();
#endif //SAP_FINAL_DOCTOR_H