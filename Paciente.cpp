#include "Paciente.h"
#include <regex>
#include <limits>
#include <cstdlib>

Paciente::Paciente() : id(0), nombre(""), fecha_ingreso(""), historial_clinico(""), DNI("") {}

void Paciente::registrarPaciente() {
    std::cout << "Ingrese el nombre del paciente: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nombre);

    std::cout << "Ingrese el DNI: ";
    std::getline(std::cin, DNI);

    std::cout << "Ingrese la fecha de ingreso (YYYY-MM-DD): ";
    std::getline(std::cin, fecha_ingreso);

    if (nombre.empty() || DNI.empty() || !std::regex_match(fecha_ingreso, std::regex("\\d{4}-\\d{2}-\\d{2}"))) {
        std::cerr << "Datos inválidos. Intente de nuevo.\n";
        return;
    }

    id = rand() % 10000;
    std::cout << "Paciente registrado con ID: " << id << "\n";
}

void Paciente::buscarPaciente() {
    std::cout << "Buscando paciente...\n";
}

void Paciente::modificarPaciente() {
    std::cout << "Modificando datos del paciente...\n";
}

void Paciente::eliminarPaciente() {
    std::cout << "Confirmar eliminación (s/n): ";
    char confirmacion;
    std::cin >> confirmacion;
    if (confirmacion == 's' || confirmacion == 'S') {
        std::cout << "Paciente eliminado.\n";
    }
}

void Paciente::agregarHistorialClinico() {
    std::cout << "Ingrese el historial clínico a agregar: ";
    std::string nuevo_historial;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nuevo_historial);

    historial_clinico += "\n" + nuevo_historial;
    std::cout << "Historial actualizado con éxito.\n";
}
