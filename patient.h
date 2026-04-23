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

void savePatients();
void loadPatients();
void register_Patient();

/* FIX: header declared updatePatient() but patient.c implemented update_Patient()
   — unified to update_Patient to match the implementation. */
void update_Patient(int PatientID);

/* FIX: Added searchPatientByID — a silent lookup used internally and by report.c.
   retrieve_patient() both finds AND prints; report.c only needs to find. */
struct Patient* searchPatientByID(int PatientID);
struct Patient* retrieve_patient(int PatientID);

#endif
