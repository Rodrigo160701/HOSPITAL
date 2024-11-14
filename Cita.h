#ifndef CITA_H
#define CITA_H

#include <iostream>
#include <string>
#include "Paciente.h"
#include "Medico.h"

class Cita {
private:
    int id;
    std::string fecha;
    int urgencia;
    Paciente* paciente;
    Medico* medico;

public:
    Cita(int id, std::string fecha, int urgencia, Paciente* paciente, Medico* medico)
        : id(id), fecha(fecha), urgencia(urgencia), paciente(paciente), medico(medico) {}

    void asignarCita();
    void modificarCita(std::string nuevaFecha, int nuevaUrgencia);
    void cancelarCita();
    void mostrarDatos() const;
};

#endif
