#ifndef SAP_FINAL_PATIENT_H
#define SAP_FINAL_PATIENT_H
struct Patient {
    int PatientID;
    char name[20];
    int age;
    char gender[10];
    char contact[100];
    char medical_history[100];
    struct Doctor* Doctor;
    struct Patient* next;
    struct Patient* prev;
};
void registerPatient();
void updatePatient(int PatientID);
void retrievePatient(int PatientID);
#endif //SAP_FINAL_PATIENT_H
