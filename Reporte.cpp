#include "Reporte.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

void Reporte::menuReportes() {
    int opcion;
    do {
        std::cout << "\n--- Menú Reportes ---\n";
        std::cout << "1. Reportes de Pacientes\n";
        std::cout << "2. Reportes de Médicos\n";
        std::cout << "3. Reporte de Citas\n";
        std::cout << "0. Volver al Menú Principal\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            menuReportesPacientes();
            break;
        case 2:
            menuReportesMedicos();
            break;
        case 3:
            menuReportesCitas();
            break;
        case 0:
            std::cout << "Volviendo al Menú Principal...\n";
            break;
        default:
            std::cout << "Opción inválida. Intente nuevamente.\n";
        }
    } while (opcion != 0);
}

void Reporte::menuReportesPacientes() {
    int opcion;
    do {
        std::cout << "\n--- Reportes de Pacientes ---\n";
        std::cout << "1. Reporte por Fechas de Ingreso\n";
        std::cout << "2. Pacientes sin Historial Clínico\n";
        std::cout << "0. Volver al Menú Reportes\n";
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
            std::cout << "Volviendo al Menú Reportes...\n";
            break;
        default:
            std::cout << "Opción inválida. Intente nuevamente.\n";
        }
    } while (opcion != 0);
}

void Reporte::menuReportesMedicos() {
    int opcion;
    do {
        std::cout << "\n--- Reportes de Médicos ---\n";
        std::cout << "1. Médicos por Especialidad\n";
        std::cout << "2. Médicos con sus Pacientes\n";
        std::cout << "0. Volver al Menú Reportes\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            reporteMedicosPorEspecialidad();
            break;
        case 2:
            reporteMedicosConPacientes();
            break;
        case 0:
            std::cout << "Volviendo al Menú Reportes...\n";
            break;
        default:
            std::cout << "Opción inválida. Intente nuevamente.\n";
        }
    } while (opcion != 0);
}
void Reporte::menuReportesCitas() {
    int opcion;
    do {
        std::cout << "\n--- Reportes de Citas ---\n";
        std::cout << "1. Citas por Fecha\n";
        std::cout << "2. Citas por Prioridad\n";
        std::cout << "0. Volver al Menú Reportes\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();
        switch (opcion) {
        case 1:
            reporteCitasPorFecha();
            break;
        case 2:
            reporteCitasPorPrioridad();
            break;
        case 0:
            std::cout << "Volviendo al Menú Reportes...\n";
            break;
        default:
            std::cout << "Opción inválida. Intente nuevamente.\n";
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
        if (linea.find("id") == 0) continue; // Saltar cabecera

        std::stringstream ss(linea);
        std::string id, nombre, dni, fechaIngreso, historial;
        std::getline(ss, id, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, dni, ',');
        std::getline(ss, fechaIngreso, ',');
        std::getline(ss, historial);

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

    if (!hayPacientes) {
        std::cout << "Todos los pacientes tienen historial clínico.\n";
    }
    archivo.close();
}

void Reporte::reporteMedicosPorEspecialidad() {
    std::ifstream archivo("medicos.csv");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de médicos.\n";
        return;
    }

    std::string linea;
    std::map<std::string, std::vector<std::string>> medicosPorEspecialidad;

    while (std::getline(archivo, linea)) {
        if (linea.find("id") == 0) continue;

        std::stringstream ss(linea);
        std::string id, nombre, especialidad, dni;
        std::getline(ss, id, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, especialidad, ',');
        std::getline(ss, dni, ',');

        medicosPorEspecialidad[especialidad].push_back("ID: " + id + ", Nombre: " + nombre + ", DNI: " + dni);
    }
    archivo.close();

    std::cout << "\n--- Reporte de Médicos por Especialidad ---\n";
    for (const auto& [especialidad, medicos] : medicosPorEspecialidad) {
        std::cout << "Especialidad: " << especialidad << "\n";
        for (const auto& medico : medicos) {
            std::cout << "  " << medico << "\n";
        }
    }
}

void Reporte::reporteMedicosConPacientes() {
    std::ifstream archivoCitas("citas.csv");
    std::ifstream archivoMedicos("medicos.csv");
    std::ifstream archivoPacientes("pacientes.csv");

    if (!archivoCitas || !archivoMedicos || !archivoPacientes) {
        std::cerr << "Error al abrir uno o más archivos necesarios.\n";
        return;
    }

    std::map<int, std::string> medicos;
    std::map<int, std::string> pacientes;
    std::map<int, std::vector<int>> medicosConPacientes;

    std::string linea;

    while (std::getline(archivoMedicos, linea)) {
        if (linea.find("id") == 0) continue;
        std::stringstream ss(linea);
        std::string id, nombre;
        std::getline(ss, id, ',');
        std::getline(ss, nombre, ',');
        medicos[std::stoi(id)] = nombre;
    }

    while (std::getline(archivoPacientes, linea)) {
        if (linea.find("id") == 0) continue;
        std::stringstream ss(linea);
        std::string id, nombre;
        std::getline(ss, id, ',');
        std::getline(ss, nombre, ',');
        pacientes[std::stoi(id)] = nombre;
    }

    while (std::getline(archivoCitas, linea)) {
        if (linea.find("id_cita") == 0) continue;
        std::stringstream ss(linea);
        std::string _, pacienteId, medicoId;
        std::getline(ss, _, ',');
        std::getline(ss, pacienteId, ',');
        std::getline(ss, medicoId, ',');
        medicosConPacientes[std::stoi(medicoId)].push_back(std::stoi(pacienteId));
    }

    std::cout << "\n--- Reporte de Médicos con sus Pacientes ---\n";
    for (const auto& [medicoId, listaPacientes] : medicosConPacientes) {
        std::cout << "Médico: " << medicos[medicoId] << " (ID: " << medicoId << ")\n";
        for (int pacienteId : listaPacientes) {
            std::cout << "  - Paciente: " << pacientes[pacienteId] << " (ID: " << pacienteId << ")\n";
        }
    }
}

void Reporte::reporteCitasPorFecha() {
    std::ifstream archivoCitas("citas.csv");
    if (!archivoCitas) {
        std::cerr << "Error al abrir el archivo de citas.\n";
        return;
    }

    std::string linea;
    std::map<std::string, std::vector<std::string>> citasPorFecha;

    while (std::getline(archivoCitas, linea)) {
        if (linea.find("id_cita") == 0) continue;

        std::stringstream ss(linea);
        std::string idCita, pacienteId, medicoId, fecha, urgencia;
        std::getline(ss, idCita, ',');
        std::getline(ss, pacienteId, ',');
        std::getline(ss, medicoId, ',');
        std::getline(ss, fecha, ',');
        std::getline(ss, urgencia, ',');

        std::string cita = "ID Cita: " + idCita + ", Paciente ID: " + pacienteId + ", Médico ID: " + medicoId + ", Urgencia: " + urgencia;
        citasPorFecha[fecha].push_back(cita);
    }
    archivoCitas.close();

    std::cout << "\n--- Reporte de Citas por Fecha ---\n";
    for (const auto& [fecha, citas] : citasPorFecha) {
        std::cout << "Fecha: " << fecha << "\n";
        for (const auto& cita : citas) {
            std::cout << "  " << cita << "\n";
        }
    }
}
void Reporte::reporteCitasPorPrioridad() {
    std::ifstream archivo("citas.csv");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de citas.\n";
        return;
    }

    std::string linea;
    std::map<int, std::vector<std::string>> citasPorPrioridad;

    while (std::getline(archivo, linea)) {
        if (linea.find("id_cita") == 0) continue;
        std::stringstream ss(linea);
        std::string idCita, pacienteId, medicoId, fecha, urgencia;
        std::getline(ss, idCita, ',');
        std::getline(ss, pacienteId, ',');
        std::getline(ss, medicoId, ',');
        std::getline(ss, fecha, ',');
        std::getline(ss, urgencia, ',');

        int prioridad = std::stoi(urgencia);
        std::string cita = "ID Cita: " + idCita + ", Fecha: " + fecha + ", Paciente ID: " + pacienteId + ", Médico ID: " + medicoId;
        citasPorPrioridad[prioridad].push_back(cita);
    }
    archivo.close();
    std::cout << "\n--- Reporte de Citas por Prioridad ---\n";
    for (int prioridad = 1; prioridad <= 5; ++prioridad) {
        std::cout << "Prioridad " << prioridad << ":\n";
        if (citasPorPrioridad[prioridad].empty()) {
            std::cout << "  No hay citas con esta prioridad.\n";
        }
        else {
            for (const auto& cita : citasPorPrioridad[prioridad]) {
                std::cout << "  " << cita << "\n";
            }
        }
    }
}