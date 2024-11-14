#include "Cita.h"

void Cita::asignarCita() {
    std::cout << "Cita asignada en fecha: " << fecha << " con urgencia: " << urgencia << std::endl;
}

void Cita::modificarCita(std::string nuevaFecha, int nuevaUrgencia) {
    fecha = nuevaFecha;
    urgencia = nuevaUrgencia;
}

void Cita::cancelarCita() {
    std::cout << "Cita cancelada." << std::endl;
}

void Cita::mostrarDatos() const {
    std::cout << "ID Cita: " << id << "\nFecha: " << fecha << "\nUrgencia: " << urgencia << std::endl;
    paciente->mostrarDatos();
    medico->mostrarDatos();
}
