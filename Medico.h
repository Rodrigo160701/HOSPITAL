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
    void registrarMedico();
    void buscarMedico();
    void modificarMedico(const std::string& nueva_especialidad, bool nueva_disponibilidad);
    void eliminarMedico();
};

#endif
