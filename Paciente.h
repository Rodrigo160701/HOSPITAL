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
    void registrarPaciente();
    void buscarPaciente();
    void modificarPaciente();
    void eliminarPaciente();
    void agregarHistorialClinico();
};

#endif
