cmake_minimum_required(VERSION 3.10)
project(sap_final C)

set(CMAKE_C_STANDARD 11)

add_executable(sap_final
        main.c
        doctor.c
        doctor.h
        patient.c
        patient.h
        appointment.c
        appointment.h
        billing.c
        billing.h
        report.c
        globals.c
        globals.h)
