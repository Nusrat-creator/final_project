#ifndef SAP_FINAL_APPOINTMENT_H
#define SAP_FINAL_APPOINTMENT_H
struct Patient;
struct Doctor;
struct Appointment {
    int appointmentID;
    struct Patient* patientPtr;
    struct Doctor* doctorPtr;
    char date[15];
    char time[10];
    char status[20];
    struct Appointment* prev;
    struct Appointment* next;
};
void saveAppointments();
void loadAppointments();
void addAppointment(int patientID);
void deleteAppointment(int appointmentID);
struct Appointment* searchAppointmentByID(int appointmentID);
void displayAllAppointments();
#endif //SAP_FINAL_APPOINTMENT_H