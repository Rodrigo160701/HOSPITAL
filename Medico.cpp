#include "Medico.h"
#include <regex>
#include <limits>
#include <cstdlib>

// Constructor por defecto
Medico::Medico() : id(0), nombre(""), especialidad(""), DNI(""), disponibilidad(false) {}

// Menú de médicos
void Medico::menuMedico() {
    int opcion;
    do {
        std::cout << "\nMenú de Médicos:\n"
            << "1. Registrar Médico\n"
            << "2. Buscar Médico\n"
            << "3. Generar Reporte\n"
            << "4. Volver al menú principal\n"
            << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
        case 1:
            registrarMedico();
            break;
        case 2:
            buscarMedico();
            break;
        case 3:
            generarReporte();
            break;
        case 4:
            std::cout << "Volviendo al menú principal...\n";
            break;
        default:
            std::cerr << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 4);
}

// Registrar médico
void Medico::registrarMedico() {
    std::cout << "Ingrese el nombre del médico: ";
    std::getline(std::cin, nombre);

    std::cout << "Ingrese la especialidad: ";
    std::getline(std::cin, especialidad);

    std::cout << "Ingrese el DNI: ";
    std::getline(std::cin, DNI);

    if (nombre.empty() || especialidad.empty() || DNI.empty()) {
        std::cerr << "Datos inválidos. Intente de nuevo.\n";
        return;
    }

    id = rand() % 10000; // Generar un ID único
    disponibilidad = true; // Por defecto, el médico está disponible
    std::cout << "Médico registrado con ID: " << id << "\n";
}

// Buscar médico
void Medico::buscarMedico() {
    std::string criterio;
    std::cout << "Ingrese el ID, Nombre, DNI o Especialidad para buscar: ";
    std::getline(std::cin, criterio);

    // Simulación: verificar si el criterio coincide con algo
    if (criterio == "Cardiología") { // Simulación
        std::cout << "Médico encontrado: Dr. García, Especialidad: Cardiología, DNI: 12345678X\n";
        modificarMedico();
    }
    else {
        std::cerr << "No se encontró ningún médico con el criterio proporcionado.\n";
    }
}

// Modificar médico
void Medico::modificarMedico() {
    std::cout << "¿Desea modificar la especialidad del médico? (s/n): ";
    char confirmacion;
    std::cin >> confirmacion;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (confirmacion == 's' || confirmacion == 'S') {
        std::cout << "Ingrese la nueva especialidad: ";
        std::getline(std::cin, especialidad);
    }

    std::cout << "¿Desea cambiar la disponibilidad del médico? (s/n): ";
    std::cin >> confirmacion;
    if (confirmacion == 's' || confirmacion == 'S') {
        disponibilidad = !disponibilidad;
        std::cout << "Disponibilidad actualizada.\n";
    }

    std::cout << "Datos del médico modificados con éxito.\n";
}

// Eliminar médico
void Medico::eliminarMedico() {
    std::cout << "Confirmar eliminación del médico (s/n): ";
    char confirmacion;
    std::cin >> confirmacion;
    if (confirmacion == 's' || confirmacion == 'S') {
        std::cout << "Médico eliminado con éxito.\n";
    }
    else {
        std::cout << "Eliminación cancelada.\n";
    }
}

// Generar reportes
void Medico::generarReporte() {
    std::cout << "\nOpciones de reporte:\n"
        << "1. Médicos disponibles\n"
        << "2. Médicos por especialidad\n"
        << "3. Médicos y sus pacientes\n"
        << "Seleccione una opción: ";
    int opcion;
    std::cin >> opcion;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (opcion) {
    case 1:
        std::cout << "Generando reporte de médicos disponibles...\n";
        break;
    case 2:
        std::cout << "Generando reporte de médicos por especialidad...\n";
        break;
    case 3:
        std::cout << "Generando reporte de médicos con sus pacientes...\n";
        break;
    default:
        std::cerr << "Opción inválida.\n";
    }
}
