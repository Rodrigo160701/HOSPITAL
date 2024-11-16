#include "Medico.h"
#include <regex>
#include <limits>
#include <cstdlib>

Medico::Medico() : id(0), nombre(""), especialidad(""), DNI(""), disponibilidad(false) {}

void Medico::registrarMedico() {
    std::cout << "Ingrese el nombre del médico: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nombre);

    std::cout << "Ingrese la especialidad: ";
    std::getline(std::cin, especialidad);

    std::cout << "Ingrese el DNI: ";
    std::getline(std::cin, DNI);

    if (nombre.empty() || especialidad.empty() || DNI.empty()) {
        std::cerr << "Datos inválidos. Intente de nuevo.\n";
        return;
    }

    id = rand() % 10000;
    std::cout << "Médico registrado con ID: " << id << "\n";
}

void Medico::buscarMedico() {
    std::cout << "Buscando médico...\n";
}

void Medico::modificarMedico(const std::string& nueva_especialidad, bool nueva_disponibilidad) {
    especialidad = nueva_especialidad;
    disponibilidad = nueva_disponibilidad;
    std::cout << "Datos del médico modificados con éxito.\n";
}

void Medico::eliminarMedico() {
    std::cout << "Confirmar eliminación (s/n): ";
    char confirmacion;
    std::cin >> confirmacion;
    if (confirmacion == 's' || confirmacion == 'S') {
        std::cout << "Médico eliminado.\n";
    }
}
