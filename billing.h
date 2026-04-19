#ifndef SAP_FINAL_BILLING_H
#define SAP_FINAL_BILLING_H
struct Patient;
struct Appointment;
struct Bill {
    int billID;
    struct Patient* patientPtr;
    struct Appointment* appointmentPtr;
    char services[500];
    float totalAmount;
    char paymentStatus[20];
    struct Bill* prev;
    struct Bill* next;
};
void generateBill(int appointmentID);

#endif