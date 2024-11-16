#ifndef PACIENTE_H
#define PACIENTE_H

#include <iostream>
#include <string>

class Paciente {
private:
    int id;
    std::string nombre;
    std::string fecha_ingreso;
    std::string historial_clinico;
    std::string DNI;

public:
    Paciente();
    void menuPaciente(); // Submenú de pacientes
    void registrarPaciente(); // Registrar un paciente
    void buscarPaciente();    // Buscar un paciente
    void modificarPaciente(); // Modificar un paciente
    void eliminarPaciente();  // Eliminar un paciente
    void agregarHistorialClinico(); // Agregar historial clínico
};

#endif
