#include "Cita.h"
#include <regex>
#include <limits>

Cita::Cita() : id(""), fecha(""), urgencia(0) {}

void Cita::menuCita() {
    int opcion;
    do {
        std::cout << "\nMenú de Citas:\n"
            << "1. Asignar Cita\n"
            << "2. Buscar Cita\n"
            << "3. Generar Reporte\n"
            << "4. Volver al menú principal\n"
            << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
        case 1:
            asignarCita();
            break;
        case 2:
            buscarCita();
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

void Cita::asignarCita() {
    std::cout << "Ingrese la fecha de la cita (YYYY-MM-DD): ";
    std::getline(std::cin, fecha);

    std::cout << "Ingrese el nivel de urgencia (1-5): ";
    std::cin >> urgencia;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (fecha.empty() || urgencia < 1 || urgencia > 5) {
        std::cerr << "Datos inválidos. Intente de nuevo.\n";
        return;
    }

    id = "C01" + std::to_string(urgencia); // Generación simulada del ID
    std::cout << "Cita creada con ID: " << id << "\n";
}

void Cita::buscarCita() {
    std::cout << "Buscando cita...\n";
}

void Cita::modificarCita() {
    std::cout << "Modificando cita...\n";
}

void Cita::cancelarCita() {
    std::cout << "Cancelando cita...\n";
}

void Cita::generarReporte() {
    std::cout << "Generando reporte de citas...\n";
}
