#include "Medico.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Medico::inicializarArchivo() {
    std::ofstream archivo("medicos.csv", std::ios::app);
    if (archivo.tellp() == 0) {
        archivo << "id,nombre,especialidad,dni\n";
    }
    archivo.close();
}

void Medico::registrar() {
    std::ofstream archivo("medicos.csv", std::ios::app);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de médicos." << std::endl;
        return;
    }

    std::string nombre, especialidad, dni;
    std::cout << "Ingrese el nombre del médico: ";
    std::getline(std::cin, nombre);
    std::cout << "Ingrese la especialidad del médico: ";
    std::getline(std::cin, especialidad);
    std::cout << "Ingrese el DNI del médico: ";
    std::getline(std::cin, dni);

    if (!validarDatos(nombre, especialidad, dni)) {
        std::cerr << "Datos inválidos. Intente nuevamente." << std::endl;
        return;
    }

    int id = generarId("medicos.csv");
    archivo << id << "," << nombre << "," << especialidad << "," << dni << "\n";
    archivo.close();

    std::cout << "Médico registrado correctamente con ID " << id << "." << std::endl;
}

void Medico::buscar() {
    std::ifstream archivo("medicos.csv");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de médicos." << std::endl;
        return;
    }

    std::string criterio;
    std::cout << "Ingrese el DNI, nombre o especialidad del médico a buscar: ";
    std::getline(std::cin, criterio);

    std::string linea;
    bool encontrado = false;

    while (std::getline(archivo, linea)) {
        if (linea.find(criterio) != std::string::npos) {
            std::cout << linea << std::endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron médicos con el criterio dado." << std::endl;
    }

    archivo.close();
}

void Medico::modificar() {
    std::cout << "Función modificar aún en desarrollo." << std::endl;
}

void Medico::eliminar() {
    std::cout << "Función eliminar aún en desarrollo." << std::endl;
}

int Medico::generarId(const std::string& archivo) {
    std::ifstream entrada(archivo);
    std::string linea;
    int ultimoId = 0;

    while (std::getline(entrada, linea)) {
        std::stringstream ss(linea);
        std::string id;
        std::getline(ss, id, ',');
        if (!id.empty() && id != "id") {
            ultimoId = std::stoi(id);
        }
    }

    return ultimoId + 1;
}

bool Medico::validarDatos(const std::string& nombre, const std::string& especialidad, const std::string& dni) {
    return !nombre.empty() && !especialidad.empty() && dni.size() == 9 && std::isdigit(dni[0]);
}
