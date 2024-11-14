#ifndef SERVICIO_H
#define SERVICIO_H

#include <iostream>
#include <string>

class Servicio {
private:
    int id;
    std::string nombre_servicio;
    std::string descripcion;

public:
    Servicio(int id, std::string nombre_servicio, std::string descripcion)
        : id(id), nombre_servicio(nombre_servicio), descripcion(descripcion) {}

    void agregarServicio();
    void modificarServicio(std::string nuevo_nombre, std::string nueva_descripcion);
    void mostrarDatos() const;
};

#endif
