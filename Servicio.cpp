#include "Servicio.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Servicio::inicializarArchivo() {
    std::ofstream archivo("servicios.csv", std::ios::app);
    if (archivo.tellp() == 0) {
        archivo << "id,nombre,descripcion\n";
    }
    archivo.close();
}

void Servicio::registrar() {
    std::ofstream archivo("servicios.csv", std::ios::app);
    std::string nombre, descripcion;
    std::cout << "Nombre del servicio: ";
    std::getline(std::cin, nombre);
    std::cout << "Descripción del servicio: ";
    std::getline(std::cin, descripcion);

    if (!validarDatos(nombre, descripcion)) {
        std::cerr << "Datos inválidos. Intente nuevamente.\n";
        return;
    }

    int id = generarId("servicios.csv");
    archivo << id << "," << nombre << "," << descripcion << "\n";
    archivo.close();
    std::cout << "Servicio registrado con ID: " << id << "\n";
}

int Servicio::buscar() {
    int opcion;
    std::cout << "\n--- Buscar Servicio ---\n";
    std::cout << "1. Buscar por ID o Nombre\n";
    std::cout << "2. Mostrar toda la lista de servicios\n";
    std::cout << "Seleccione una opción: ";
    std::cin >> opcion;
    std::cin.ignore();

    if (opcion == 1) {
        return buscarPorCriterio();
    }
    else if (opcion == 2) {
        mostrarListaCompleta();
        return -1;
    }
    else {
        std::cout << "Opción inválida.\n";
        return -1;
    }
}

int Servicio::buscarPorCriterio() {
    std::ifstream archivo("servicios.csv");
    std::string criterio, linea;
    std::cout << "Ingrese el ID o Nombre del servicio a buscar: ";
    std::getline(std::cin, criterio);

    int id = -1;
    while (std::getline(archivo, linea)) {
        if (linea.find(criterio) != std::string::npos) {
            std::cout << "Servicio encontrado: " << linea << "\n";
            std::stringstream ss(linea);
            std::string idStr;
            std::getline(ss, idStr, ',');
            id = std::stoi(idStr);
            break;
        }
    }

    if (id == -1) {
        std::cout << "No se encontró ningún servicio con ese criterio.\n";
    }

    return id;
}

void Servicio::mostrarListaCompleta() {
    std::ifstream archivo("servicios.csv");
    std::string linea;
    bool primeraLinea = true;

    std::cout << "\n--- Lista Completa de Servicios ---\n";
    while (std::getline(archivo, linea)) {
        if (primeraLinea) { 
            primeraLinea = false;
            continue;
        }
        std::cout << linea << "\n";
    }
    archivo.close();
}

void Servicio::menuServicioSeleccionado(int servicioId) {
    int opcion;
    do {
        std::cout << "\n--- Menú Servicio Seleccionado ---\n";
        std::cout << "1. Modificar Servicio\n";
        std::cout << "2. Eliminar Servicio\n";
        std::cout << "0. Volver al Menú Servicio\n";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            modificar(servicioId);
            break;
        case 2:
            eliminar(servicioId);
            break;
        case 0:
            break;
        default:
            std::cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}

void Servicio::modificar(int servicioId) {
    std::ifstream archivoEntrada("servicios.csv");
    std::ofstream archivoTemporal("servicios_temp.csv");

    if (!archivoEntrada || !archivoTemporal) {
        std::cerr << "Error al abrir archivos.\n";
        return;
    }

    std::string linea;
    bool encontrado = false;

    while (std::getline(archivoEntrada, linea)) {
        std::stringstream ss(linea);
        std::string idStr, nombre, descripcion;
        std::getline(ss, idStr, ',');

        if (idStr == "id") {
            archivoTemporal << linea << "\n"; 
            continue;
        }

        if (std::stoi(idStr) == servicioId) {
            encontrado = true;
            std::cout << "Servicio encontrado: " << linea << "\n";

            std::cout << "Nuevo nombre del servicio (deje vacío para no modificar): ";
            std::string nuevoNombre;
            std::getline(std::cin, nuevoNombre);

            std::cout << "Nueva descripción del servicio (deje vacío para no modificar): ";
            std::string nuevaDescripcion;
            std::getline(std::cin, nuevaDescripcion);

            if (!nuevoNombre.empty()) nombre = nuevoNombre;
            if (!nuevaDescripcion.empty()) descripcion = nuevaDescripcion;

            archivoTemporal << idStr << "," << nombre << "," << descripcion << "\n";
            std::cout << "Servicio modificado correctamente.\n";
        }
        else {
            archivoTemporal << linea << "\n";
        }
    }

    archivoEntrada.close();
    archivoTemporal.close();

    std::remove("servicios.csv");
    std::rename("servicios_temp.csv", "servicios.csv");

    if (!encontrado) {
        std::cout << "Servicio no encontrado.\n";
    }
}

void Servicio::eliminar(int servicioId) {
    std::ifstream archivoEntrada("servicios.csv");
    std::ofstream archivoTemporal("servicios_temp.csv");

    if (!archivoEntrada || !archivoTemporal) {
        std::cerr << "Error al abrir archivos.\n";
        return;
    }

    std::string linea;
    bool eliminado = false;

    while (std::getline(archivoEntrada, linea)) {
        std::stringstream ss(linea);
        std::string idStr;
        std::getline(ss, idStr, ',');

        if (idStr == "id") {
            archivoTemporal << linea << "\n"; 
            continue;
        }

        if (std::stoi(idStr) == servicioId) {
            eliminado = true;
            std::cout << "Servicio eliminado: " << linea << "\n";
        }
        else {
            archivoTemporal << linea << "\n";
        }
    }

    archivoEntrada.close();
    archivoTemporal.close();

    std::remove("servicios.csv");
    std::rename("servicios_temp.csv", "servicios.csv");

    if (!eliminado) {
        std::cout << "Servicio no encontrado.\n";
    }
}

int Servicio::generarId(const std::string& archivo) {
    std::ifstream entrada(archivo);
    std::string linea;
    int ultimoId = 0;

    while (std::getline(entrada, linea)) {
        std::stringstream ss(linea);
        std::string idStr;
        std::getline(ss, idStr, ',');
        if (!idStr.empty() && idStr != "id") {
            ultimoId = std::stoi(idStr);
        }
    }

    return ultimoId + 1;
}

bool Servicio::validarDatos(const std::string& nombre, const std::string& descripcion) {
    return !nombre.empty() && !descripcion.empty();
}
