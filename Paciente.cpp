#include "Paciente.h"
#include <regex>
#include <limits>
#include <cstdlib>
#include <vector>

// Constructor por defecto
Paciente::Paciente() : id(0), nombre(""), fecha_ingreso(""), historial_clinico(""), DNI("") {}

// Men� de pacientes
void Paciente::menuPaciente() {
    int opcion;
    do {
        std::cout << "\nMen� de Pacientes:\n"
            << "1. Registrar Paciente\n"
            << "2. Buscar Paciente\n"
            << "3. Volver al men� principal\n"
            << "Seleccione una opci�n: ";
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
            std::cout << "Volviendo al men� principal...\n";
            break;
        default:
            std::cerr << "Opci�n inv�lida. Intente de nuevo.\n";
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
        std::cerr << "Datos inv�lidos. Intente de nuevo.\n";
        return;
    }

    id = rand() % 10000; // Generar un ID �nico
    std::cout << "Paciente registrado con ID: " << id << "\n";
}

// Buscar paciente
void Paciente::buscarPaciente() {
    std::string criterio;
    std::cout << "Ingrese el ID, Nombre, DNI o Fecha de ingreso para buscar: ";
    std::getline(std::cin, criterio);

    // Simulaci�n: verificar si el criterio coincide con algo (solo mostramos un ejemplo)
    if (criterio == "12345") { // Reemplazar por b�squeda real en la base de datos
        std::cout << "Paciente encontrado: Juan P�rez, DNI: 12345678X, Fecha de ingreso: 2024-01-01\n";
        modificarPaciente(); // Despu�s de encontrarlo, llama a opciones adicionales
    }
    else {
        std::cerr << "No se encontr� ning�n paciente con el criterio proporcionado.\n";
    }
}

// Modificar paciente
void Paciente::modificarPaciente() {
    std::cout << "�Desea modificar el nombre del paciente? (s/n): ";
    char confirmacion;
    std::cin >> confirmacion;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (confirmacion == 's' || confirmacion == 'S') {
        std::cout << "Ingrese el nuevo nombre: ";
        std::getline(std::cin, nombre);
    }

    std::cout << "�Desea modificar el DNI del paciente? (s/n): ";
    std::cin >> confirmacion;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (confirmacion == 's' || confirmacion == 'S') {
        std::cout << "Ingrese el nuevo DNI: ";
        std::getline(std::cin, DNI);
    }

    std::cout << "Datos modificados con �xito.\n";
}

// Eliminar paciente
void Paciente::eliminarPaciente() {
    std::cout << "Confirmar eliminaci�n del paciente (s/n): ";
    char confirmacion;
    std::cin >> confirmacion;
    if (confirmacion == 's' || confirmacion == 'S') {
        std::cout << "Paciente eliminado con �xito.\n";
    }
    else {
        std::cout << "Eliminaci�n cancelada.\n";
    }
}

// Agregar historial cl�nico
void Paciente::agregarHistorialClinico() {
    std::cout << "Ingrese el historial cl�nico a agregar: ";
    std::string nuevo_historial;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nuevo_historial);

    historial_clinico += "\n" + nuevo_historial;
    std::cout << "Historial actualizado con �xito.\n";
}
