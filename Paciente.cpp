#include "Paciente.h"

void Paciente::registrarPaciente() {
    std::cout << "Paciente registrado: " << nombre << " con DNI: " << DNI << std::endl;
}

void Paciente::modificarPaciente(std::string nuevo_nombre, std::string nuevo_historial) {
    nombre = nuevo_nombre;
    historial_clinico = nuevo_historial;
}

void Paciente::agregarHistorialClinico(std::string nuevo_historial) {
    historial_clinico += "\n" + nuevo_historial;
}

void Paciente::mostrarDatos() const {
    std::cout << "ID: " << id << "\nNombre: " << nombre << "\nDNI: " << DNI << "\nHistorial: " << historial_clinico << std::endl;
}
