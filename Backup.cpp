#include "Backup.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <ctime>

namespace fs = std::filesystem;

void Backup::menuBackup() {
    int opcion;
    do {
        std::cout << "\n--- Menú Backup ---\n";
        std::cout << "1. Backup Pacientes\n";
        std::cout << "2. Backup Médicos\n";
        std::cout << "3. Backup Citas\n";
        std::cout << "4. Backup Servicios\n";
        std::cout << "5. Backup de Todo\n";
        std::cout << "0. Volver al Menú Principal\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            backupPacientes();
            break;
        case 2:
            backupMedicos();
            break;
        case 3:
            backupCitas();
            break;
        case 4:
            backupServicios();
            break;
        case 5:
            backupTodo();
            break;
        case 0:
            std::cout << "Volviendo al Menú Principal...\n";
            break;
        default:
            std::cout << "Opción inválida. Intente nuevamente.\n";
        }
    } while (opcion != 0);
}

void Backup::backupPacientes() {
    std::string carpeta = crearCarpetaBackup();
    copiarArchivo("pacientes.csv", carpeta + "/pacientes.csv");
    std::cout << "Backup de pacientes realizado en: " << carpeta << std::endl;
}

void Backup::backupMedicos() {
    std::string carpeta = crearCarpetaBackup();
    copiarArchivo("medicos.csv", carpeta + "/medicos.csv");
    std::cout << "Backup de médicos realizado en: " << carpeta << std::endl;
}

void Backup::backupCitas() {
    std::string carpeta = crearCarpetaBackup();
    copiarArchivo("citas.csv", carpeta + "/citas.csv");
    std::cout << "Backup de citas realizado en: " << carpeta << std::endl;
}

void Backup::backupServicios() {
    std::string carpeta = crearCarpetaBackup();
    copiarArchivo("servicios.csv", carpeta + "/servicios.csv");
    std::cout << "Backup de servicios realizado en: " << carpeta << std::endl;
}

void Backup::backupTodo() {
    std::string carpeta = crearCarpetaBackup();
    copiarArchivo("pacientes.csv", carpeta + "/pacientes.csv");
    copiarArchivo("medicos.csv", carpeta + "/medicos.csv");
    copiarArchivo("citas.csv", carpeta + "/citas.csv");
    copiarArchivo("servicios.csv", carpeta + "/servicios.csv");
    std::cout << "Backup de todos los archivos realizado en: " << carpeta << std::endl;
}

std::string Backup::crearCarpetaBackup() {
    std::string baseCarpeta = "backup";
    fs::create_directories(baseCarpeta);

    // Obtener la fecha y hora actual
    time_t ahora = time(0);
    tm* tiempoLocal = localtime(&ahora);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", tiempoLocal);

    std::string carpeta = baseCarpeta + "/" + std::string(buffer);
    fs::create_directories(carpeta);
    return carpeta;
}

void Backup::copiarArchivo(const std::string& origen, const std::string& destino) {
    std::ifstream archivoOrigen(origen, std::ios::binary);
    std::ofstream archivoDestino(destino, std::ios::binary);

    if (!archivoOrigen) {
        std::cerr << "Error: No se pudo abrir el archivo origen: " << origen << std::endl;
        return;
    }
    if (!archivoDestino) {
        std::cerr << "Error: No se pudo crear el archivo destino: " << destino << std::endl;
        return;
    }

    archivoDestino << archivoOrigen.rdbuf();
    archivoOrigen.close();
    archivoDestino.close();
}
