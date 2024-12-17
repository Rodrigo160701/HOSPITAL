#include "HOSPITAL.h"
#include <iostream>

void menuPaciente() {
    int opcion;
    do {
        std::cout << "\n--- Menú Paciente ---\n";
        std::cout << "1. Registrar Paciente\n";
        std::cout << "2. Buscar Paciente\n";
        std::cout << "0. Volver al Menú Principal\n";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            Paciente::registrar();
            break;
        case 2: {
            int id = Paciente::buscar();
            if (id != -1) {
                Paciente::menuPacienteSeleccionado(id);
            }
            break;
        }
        case 0:
            break;
        default:
            std::cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}

void menuMedico() {
    int opcion;
    do {
        std::cout << "\n--- Menú Médico ---\n";
        std::cout << "1. Registrar Médico\n";
        std::cout << "2. Buscar Médico\n";
        std::cout << "0. Volver al Menú Principal\n";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            Medico::registrar();
            break;
        case 2: {
            int id = Medico::buscar();
            if (id != -1) {
                Medico::menuMedicoSeleccionado(id);
            }
            break;
        }
        case 0:
            break;
        default:
            std::cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}

void menuCita() {
    int opcion;
    do {
        std::cout << "\n--- Menú Cita ---\n";
        std::cout << "1. Asignar Cita\n";
        std::cout << "2. Buscar Cita\n";
        std::cout << "0. Volver al Menú Principal\n";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            Cita::asignar();
            break;
        case 2: {
            int id = Cita::buscar();
            if (id != -1) {
                Cita::menuCitaSeleccionada(id);
            }
            break;
        }
        case 0:
            break;
        default:
            std::cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}

void menuServicio() {
    int opcion;
    do {
        std::cout << "\n--- Menú Servicio ---\n";
        std::cout << "1. Registrar Servicio\n";
        std::cout << "2. Buscar Servicio\n";
        std::cout << "0. Volver al Menú Principal\n";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            Servicio::registrar();
            break;
        case 2: {
            int id = Servicio::buscar();
            if (id != -1) {
                Servicio::menuServicioSeleccionado(id);
            }
            break;
        }
        case 0:
            break;
        default:
            std::cout << "Opción inválida.\n";
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
        std::cout << "4. Servicio\n";
        std::cout << "5. Reportes\n";
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
        case 4:
            menuServicio();
            break;
        case 5:
            Reporte::menuReportes();
            break;
        case 0:
            std::cout << "Saliendo...\n";
            break;
        default:
            std::cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}

int main() {
    Paciente::inicializarArchivo();
    Medico::inicializarArchivo();
    Cita::inicializarArchivo();
    Servicio::inicializarArchivo();
    menuPrincipal();
    return 0;
}
