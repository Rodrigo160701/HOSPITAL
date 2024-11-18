#include "Hospital.h"
#include <iostream>

void menuPaciente() {
    int opcion;
    do {
        std::cout << "\n--- Menú Paciente ---\n";
        std::cout << "1. Registrar Paciente\n";
        std::cout << "2. Buscar Paciente\n";
        std::cout << "3. Modificar Paciente\n";
        std::cout << "4. Eliminar Paciente\n";
        std::cout << "0. Volver al Menú Principal\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            Paciente::registrar();
            break;
        case 2:
            Paciente::buscar();
            break;
        case 3:
            Paciente::modificar();
            break;
        case 4:
            Paciente::eliminar();
            break;
        case 0:
            std::cout << "Volviendo al Menú Principal..." << std::endl;
            break;
        default:
            std::cout << "Opción no válida. Intente nuevamente." << std::endl;
        }
    } while (opcion != 0);
}

void menuMedico() {
    int opcion;
    do {
        std::cout << "\n--- Menú Médico ---\n";
        std::cout << "1. Registrar Médico\n";
        std::cout << "2. Buscar Médico\n";
        std::cout << "3. Modificar Médico\n";
        std::cout << "4. Eliminar Médico\n";
        std::cout << "0. Volver al Menú Principal\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            Medico::registrar();
            break;
        case 2:
            Medico::buscar();
            break;
        case 3:
            Medico::modificar();
            break;
        case 4:
            Medico::eliminar();
            break;
        case 0:
            std::cout << "Volviendo al Menú Principal..." << std::endl;
            break;
        default:
            std::cout << "Opción no válida. Intente nuevamente." << std::endl;
        }
    } while (opcion != 0);
}

void menuCita() {
    int opcion;
    do {
        std::cout << "\n--- Menú Cita ---\n";
        std::cout << "1. Asignar Cita\n";
        std::cout << "2. Buscar Cita\n";
        std::cout << "3. Modificar Cita\n";
        std::cout << "4. Cancelar Cita\n";
        std::cout << "0. Volver al Menú Principal\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            Cita::asignar();
            break;
        case 2:
            Cita::buscar();
            break;
        case 3:
            Cita::modificar();
            break;
        case 4:
            Cita::cancelar();
            break;
        case 0:
            std::cout << "Volviendo al Menú Principal..." << std::endl;
            break;
        default:
            std::cout << "Opción no válida. Intente nuevamente." << std::endl;
        }
    } while (opcion != 0);
}

void menuPrincipal() {
    int opcion;
    do {
        std::cout << "\n--- Menú Principal ---\n";
        std::cout << "1. Paciente\n";
        std::cout << "2. Médico\n";
        std::cout << "3. Cita\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            menuPaciente();
            break;
        case 2:
            menuMedico();
            break;
        case 3:
            menuCita();
            break;
        case 0:
            std::cout << "Saliendo del programa..." << std::endl;
            break;
        default:
            std::cout << "Opción no válida. Intente nuevamente." << std::endl;
        }
    } while (opcion != 0);
}

int main() {
    Paciente::inicializarArchivo();
    Medico::inicializarArchivo();
    Cita::inicializarArchivo();
    menuPrincipal();
    return 0;
}
