#include "Paciente.h"
#include <regex>
#include <limits>
#include <cstdlib>
#include <vector>

// Constructor por defecto
Paciente::Paciente() : id(0), nombre(""), fecha_ingreso(""), historial_clinico(""), DNI("") {}

// Menú de pacientes
void Paciente::menuPaciente() {
    int opcion;
    do {
        std::cout << "\nMenú de Pacientes:\n"
            << "1. Registrar Paciente\n"
            << "2. Buscar Paciente\n"
            << "3. Volver al menú principal\n"
            << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
        case 1:
            registrarPaciente();
            break;
        case 2:
            buscarPaciente();
            break;
        case 3:
            std::cout << "Volviendo al menú principal...\n";
            break;
        default:
            std::cerr << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 3);
}

// Registrar paciente
void Paciente::registrarPaciente() {
    std::cout << "Ingrese el nombre del paciente: ";
    std::getline(std::cin, nombre);

    std::cout << "Ingrese el DNI: ";
    std::getline(std::cin, DNI);

    std::cout << "Ingrese la fecha de ingreso (YYYY-MM-DD): ";
    std::getline(std::cin, fecha_ingreso);

    if (nombre.empty() || DNI.empty() || !std::regex_match(fecha_ingreso, std::regex("\\d{4}-\\d{2}-\\d{2}"))) {
        std::cerr << "Datos inválidos. Intente de nuevo.\n";
        return;
    }

    id = rand() % 10000; // Generar un ID único
    std::cout << "Paciente registrado con ID: " << id << "\n";
}

// Buscar paciente
void Paciente::buscarPaciente() {
    std::string criterio;
    std::cout << "Ingrese el ID, Nombre, DNI o Fecha de ingreso para buscar: ";
    std::getline(std::cin, criterio);

    // Simulación: verificar si el criterio coincide con algo (solo mostramos un ejemplo)
    if (criterio == "12345") { // Reemplazar por búsqueda real en la base de datos
        std::cout << "Paciente encontrado: Juan Pérez, DNI: 12345678X, Fecha de ingreso: 2024-01-01\n";
        modificarPaciente(); // Después de encontrarlo, llama a opciones adicionales
    }
    else {
        std::cerr << "No se encontró ningún paciente con el criterio proporcionado.\n";
    }
}

// Modificar paciente
void Paciente::modificarPaciente() {
    std::cout << "¿Desea modificar el nombre del paciente? (s/n): ";
    char confirmacion;
    std::cin >> confirmacion;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (confirmacion == 's' || confirmacion == 'S') {
        std::cout << "Ingrese el nuevo nombre: ";
        std::getline(std::cin, nombre);
    }

    std::cout << "¿Desea modificar el DNI del paciente? (s/n): ";
    std::cin >> confirmacion;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (confirmacion == 's' || confirmacion == 'S') {
        std::cout << "Ingrese el nuevo DNI: ";
        std::getline(std::cin, DNI);
    }

    std::cout << "Datos modificados con éxito.\n";
}

// Eliminar paciente
void Paciente::eliminarPaciente() {
    std::cout << "Confirmar eliminación del paciente (s/n): ";
    char confirmacion;
    std::cin >> confirmacion;
    if (confirmacion == 's' || confirmacion == 'S') {
        std::cout << "Paciente eliminado con éxito.\n";
    }
    else {
        std::cout << "Eliminación cancelada.\n";
    }
}

// Agregar historial clínico
void Paciente::agregarHistorialClinico() {
    std::cout << "Ingrese el historial clínico a agregar: ";
    std::string nuevo_historial;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nuevo_historial);

    historial_clinico += "\n" + nuevo_historial;
    std::cout << "Historial actualizado con éxito.\n";
}
