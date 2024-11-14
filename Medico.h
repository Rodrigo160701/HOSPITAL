#ifndef MEDICO_H
#define MEDICO_H

#include <iostream>
#include <string>

class Medico {
private:
    int id;
    std::string nombre;
    std::string especialidad;
    bool disponibilidad;

public:
    Medico(int id, std::string nombre, std::string especialidad, bool disponibilidad)
        : id(id), nombre(nombre), especialidad(especialidad), disponibilidad(disponibilidad) {}

    void registrarMedico();
    void modificarMedico(std::string nueva_especialidad, bool nueva_disponibilidad);
    void mostrarDatos() const;
};

#endif
