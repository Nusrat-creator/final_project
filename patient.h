#ifndef SAP_FINAL_PATIENT_H
#define SAP_FINAL_PATIENT_H
struct Patient {
    int PatientID;
    char name[50];
    int age;
    char gender[10];
    char contact[100];
    char medical_history[100];
    struct Doctor* Doctor;
    struct Patient* next;
    struct Patient* prev;
};
void register_Patient();
void update_Patient(int PatientID);
struct Patient* retrieve_patient(int PatientID);
void delete_Patient(int PatientID);
struct Patient* search_Patient(int PatientID);
#endif
