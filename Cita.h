#ifndef CITA_H
#define CITA_H

#include <iostream>
#include <string>
#include "Paciente.h"
#include "Medico.h"

class Cita {
private:
    std::string id;
    std::string fecha;
    int urgencia;
    Paciente paciente;
    Medico medico;

public:
    Cita();
    void menuCita(); // Submenú de citas
    void asignarCita();
    void buscarCita();
    void modificarCita();
    void cancelarCita();
    void generarReporte();
};

#endif
