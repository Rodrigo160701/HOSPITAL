#include "Medico.h"

void Medico::registrarMedico() {
    std::cout << "M�dico registrado: " << nombre << " (" << especialidad << ")" << std::endl;
}

void Medico::modificarMedico(std::string nueva_especialidad, bool nueva_disponibilidad) {
    especialidad = nueva_especialidad;
    disponibilidad = nueva_disponibilidad;
}

void Medico::mostrarDatos() const {
    std::cout << "ID: " << id << "\nNombre: " << nombre << "\nEspecialidad: " << especialidad
        << "\nDisponible: " << (disponibilidad ? "S�" : "No") << std::endl;
}
