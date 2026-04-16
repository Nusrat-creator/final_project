//
// Created by seyid on 4/14/2026.
//
#ifndef SAP_FINAL_GLOBALS_H
#define SAP_FINAL_GLOBALS_H
struct Doctor;
struct Appointment;
struct Bill;
extern struct Doctor* doctorHead;
extern struct Doctor* doctorTail;
extern struct Appointment* appointmentHead;
extern struct Appointment* appointmentTail;
extern struct Bill* billHead;
extern struct Bill* billTail;
extern int doctorCounter;
extern int patientCounter;
extern int appointmentCounter;
extern int billCounter;
#endif //SAP_FINAL_GLOBALS_H