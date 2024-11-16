#include "Cita.h"
#include <limits>

Cita::Cita() : id(""), fecha(""), urgencia(0) {}

void Cita::asignarCita() {
    std::cout << "Ingrese la fecha de la cita (YYYY-MM-DD): ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, fecha);

    std::cout << "Ingrese el nivel de urgencia (1-5): ";
    std::cin >> urgencia;

    if (fecha.empty() || urgencia < 1 || urgencia > 5) {
        std::cerr << "Datos inválidos. Intente de nuevo.\n";
        return;
    }

    id = "XY01" + std::to_string(urgencia);
    std::cout << "Cita creada con ID: " << id << "\n";
}

void Cita::buscarCita() {
    std::cout << "Buscando cita...\n";
}

void Cita::modificarCita() {
    std::cout << "Modificando datos de la cita...\n";
}

void Cita::cancelarCita() {
    std::cout << "Confirmar cancelación (s/n): ";
    char confirmacion;
    std::cin >> confirmacion;
    if (confirmacion == 's' || confirmacion == 'S') {
        std::cout << "Cita cancelada.\n";
    }
}
