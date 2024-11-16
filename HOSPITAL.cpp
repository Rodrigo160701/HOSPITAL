#include "Paciente.h"
#include "Medico.h"
#include "Cita.h"
#include <iostream>
#include <limits>

void mostrarMenuPrincipal() {
    std::cout << "\nMenú principal:\n"
        << "1. Paciente\n"
        << "2. Médico\n"
        << "3. Cita\n"
        << "4. Salir\n"
        << "Seleccione una opción: ";
}

void manejarOpcion(int opcion, Paciente& paciente, Medico& medico, Cita& cita) {
    switch (opcion) {
    case 1:
        paciente.menuPaciente();
        break;
    case 2:
        medico.menuMedico();
        break;
    case 3:
        cita.menuCita();
        break;
    case 4:
        std::cout << "Saliendo del sistema...\n";
        exit(0);
    default:
        std::cerr << "Opción inválida. Intente de nuevo.\n";
    }
}

int main() {
    std::cout << "Bienvenido al sistema de gestión hospitalaria.\n";
    Paciente paciente;
    Medico medico;
    Cita cita;

    int opcion;
    while (true) {
        mostrarMenuPrincipal();
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        manejarOpcion(opcion, paciente, medico, cita);
    }

    return 0;
}
