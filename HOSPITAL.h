#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Paciente.h"
#include "Medico.h"
#include "Cita.h"

// Declaración de funciones globales para el main
void mostrarMenuPrincipal();
void manejarOpcion(int opcion, Paciente& paciente, Medico& medico, Cita& cita);

#endif
