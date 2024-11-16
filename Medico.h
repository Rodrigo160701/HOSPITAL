#ifndef MEDICO_H
#define MEDICO_H

#include <iostream>
#include <string>

class Medico {
private:
    int id;
    std::string nombre;
    std::string especialidad;
    std::string DNI;
    bool disponibilidad;

public:
    Medico();
    void menuMedico(); // Submen� de m�dicos
    void registrarMedico();
    void buscarMedico();
    void modificarMedico();
    void eliminarMedico();
    void generarReporte();
};

#endif
