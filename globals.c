#include <stddef.h>
#include <stdio.h>
#include "doctor.h"
#include "patient.h"
#include "appointment.h"
#include "billing.h"

struct Doctor* doctorHead = NULL;
struct Doctor* doctorTail = NULL;

/* FIX: These were declared in globals.h but never defined here — caused all
   "undefined reference to patientHead/patientTail" linker errors. */
struct Patient* patientHead = NULL;
struct Patient* patientTail = NULL;

struct Appointment* appointmentHead = NULL;
struct Appointment* appointmentTail = NULL;

struct Bill* billHead = NULL;
struct Bill* billTail = NULL;

int doctorCounter = 0;
int patientCounter = 0;
int appointmentCounter = 0;
int billCounter = 0;
