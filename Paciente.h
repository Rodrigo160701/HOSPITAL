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
    Paciente(int id, std::string nombre, std::string fecha_ingreso, std::string historial_clinico, std::string DNI)
        : id(id), nombre(nombre), fecha_ingreso(fecha_ingreso), historial_clinico(historial_clinico), DNI(DNI) {}

    void registrarPaciente();
    void modificarPaciente(std::string nuevo_nombre, std::string nuevo_historial);
    void agregarHistorialClinico(std::string nuevo_historial);
    void mostrarDatos() const;
};

#endif
