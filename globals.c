#include "globals.h"
#include <stddef.h>


struct Doctor* doctorHead = NULL;
struct Doctor* doctorTail = NULL;

struct Appointment* appointmentHead = NULL;
struct Appointment* appointmentTail = NULL;

struct Bill* billHead = NULL;
struct Bill* billTail = NULL;


int doctorCounter = 0;
int patientCounter = 0;
int appointmentCounter = 0;
int billCounter = 0;