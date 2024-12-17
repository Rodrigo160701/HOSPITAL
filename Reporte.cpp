#include "Reporte.h"
#include "Paciente.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

void Reporte::menuReportes() {
    int opcion;
    do {
        std::cout << "\n--- Menú Reportes ---\n";
        std::cout << "1. Reporte por Fechas de Ingreso\n";
        std::cout << "2. Pacientes sin Historial Clínico\n";
        std::cout << "0. Volver al Menú Principal\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            reportePorFechasIngreso();
            break;
        case 2:
            reportePacientesSinHistorial();
            break;
        case 0:
            std::cout << "Volviendo al Menú Principal...\n";
            break;
        default:
            std::cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}

void Reporte::reportePorFechasIngreso() {
    std::ifstream archivo("pacientes.csv");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de pacientes.\n";
        return;
    }

    std::string linea;
    std::map<std::string, std::vector<std::string>> reportePorFecha;

    while (std::getline(archivo, linea)) {
        if (linea.find("id") == 0) continue;

        std::stringstream ss(linea);
        std::string id, nombre, dni, fechaIngreso, historial;
        std::getline(ss, id, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, dni, ',');
        std::getline(ss, fechaIngreso, ',');

        reportePorFecha[fechaIngreso].push_back("ID: " + id + ", Nombre: " + nombre + ", DNI: " + dni);
    }
    archivo.close();

    std::cout << "\n--- Reporte por Fechas de Ingreso ---\n";
    for (const auto& [fecha, pacientes] : reportePorFecha) {
        std::cout << "Fecha: " << fecha << "\n";
        for (const auto& paciente : pacientes) {
            std::cout << "  " << paciente << "\n";
        }
    }
}

void Reporte::reportePacientesSinHistorial() {
    std::ifstream archivo("pacientes.csv");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de pacientes.\n";
        return;
    }

    std::string linea;
    bool hayPacientes = false;

    std::cout << "\n--- Pacientes sin Historial Clínico ---\n";
    while (std::getline(archivo, linea)) {
        if (linea.find("id") == 0) continue;

        std::stringstream ss(linea);
        std::string id, nombre, dni, fechaIngreso, historial;
        std::getline(ss, id, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, dni, ',');
        std::getline(ss, fechaIngreso, ',');
        std::getline(ss, historial);

        if (historial.empty()) {
            hayPacientes = true;
            std::cout << "ID: " << id << ", Nombre: " << nombre << ", DNI: " << dni << ", Fecha Ingreso: " << fechaIngreso << "\n";
        }
    }
    archivo.close();

    if (!hayPacientes) {
        std::cout << "Todos los pacientes tienen historial clínico.\n";
    }
}
