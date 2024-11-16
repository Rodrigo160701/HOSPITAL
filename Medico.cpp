#include "Medico.h"
#include <regex>
#include <limits>
#include <cstdlib>

// Constructor por defecto
Medico::Medico() : id(0), nombre(""), especialidad(""), DNI(""), disponibilidad(false) {}

// Men� de m�dicos
void Medico::menuMedico() {
    int opcion;
    do {
        std::cout << "\nMen� de M�dicos:\n"
            << "1. Registrar M�dico\n"
            << "2. Buscar M�dico\n"
            << "3. Generar Reporte\n"
            << "4. Volver al men� principal\n"
            << "Seleccione una opci�n: ";
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
            std::cout << "Volviendo al men� principal...\n";
            break;
        default:
            std::cerr << "Opci�n inv�lida. Intente de nuevo.\n";
        }
    } while (opcion != 4);
}

// Registrar m�dico
void Medico::registrarMedico() {
    std::cout << "Ingrese el nombre del m�dico: ";
    std::getline(std::cin, nombre);

    std::cout << "Ingrese la especialidad: ";
    std::getline(std::cin, especialidad);

    std::cout << "Ingrese el DNI: ";
    std::getline(std::cin, DNI);

    if (nombre.empty() || especialidad.empty() || DNI.empty()) {
        std::cerr << "Datos inv�lidos. Intente de nuevo.\n";
        return;
    }

    id = rand() % 10000; // Generar un ID �nico
    disponibilidad = true; // Por defecto, el m�dico est� disponible
    std::cout << "M�dico registrado con ID: " << id << "\n";
}

// Buscar m�dico
void Medico::buscarMedico() {
    std::string criterio;
    std::cout << "Ingrese el ID, Nombre, DNI o Especialidad para buscar: ";
    std::getline(std::cin, criterio);

    // Simulaci�n: verificar si el criterio coincide con algo
    if (criterio == "Cardiolog�a") { // Simulaci�n
        std::cout << "M�dico encontrado: Dr. Garc�a, Especialidad: Cardiolog�a, DNI: 12345678X\n";
        modificarMedico();
    }
    else {
        std::cerr << "No se encontr� ning�n m�dico con el criterio proporcionado.\n";
    }
}

// Modificar m�dico
void Medico::modificarMedico() {
    std::cout << "�Desea modificar la especialidad del m�dico? (s/n): ";
    char confirmacion;
    std::cin >> confirmacion;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (confirmacion == 's' || confirmacion == 'S') {
        std::cout << "Ingrese la nueva especialidad: ";
        std::getline(std::cin, especialidad);
    }

    std::cout << "�Desea cambiar la disponibilidad del m�dico? (s/n): ";
    std::cin >> confirmacion;
    if (confirmacion == 's' || confirmacion == 'S') {
        disponibilidad = !disponibilidad;
        std::cout << "Disponibilidad actualizada.\n";
    }

    std::cout << "Datos del m�dico modificados con �xito.\n";
}

// Eliminar m�dico
void Medico::eliminarMedico() {
    std::cout << "Confirmar eliminaci�n del m�dico (s/n): ";
    char confirmacion;
    std::cin >> confirmacion;
    if (confirmacion == 's' || confirmacion == 'S') {
        std::cout << "M�dico eliminado con �xito.\n";
    }
    else {
        std::cout << "Eliminaci�n cancelada.\n";
    }
}

// Generar reportes
void Medico::generarReporte() {
    std::cout << "\nOpciones de reporte:\n"
        << "1. M�dicos disponibles\n"
        << "2. M�dicos por especialidad\n"
        << "3. M�dicos y sus pacientes\n"
        << "Seleccione una opci�n: ";
    int opcion;
    std::cin >> opcion;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (opcion) {
    case 1:
        std::cout << "Generando reporte de m�dicos disponibles...\n";
        break;
    case 2:
        std::cout << "Generando reporte de m�dicos por especialidad...\n";
        break;
    case 3:
        std::cout << "Generando reporte de m�dicos con sus pacientes...\n";
        break;
    default:
        std::cerr << "Opci�n inv�lida.\n";
    }
}
