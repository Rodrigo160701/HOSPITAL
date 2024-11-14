#include "Servicio.h"

void Servicio::agregarServicio() {
    std::cout << "Servicio agregado: " << nombre_servicio << std::endl;
}

void Servicio::modificarServicio(std::string nuevo_nombre, std::string nueva_descripcion) {
    nombre_servicio = nuevo_nombre;
    descripcion = nueva_descripcion;
}

void Servicio::mostrarDatos() const {
    std::cout << "ID Servicio: " << id << "\nNombre: " << nombre_servicio << "\nDescripción: " << descripcion << std::endl;
}
