#include "Paciente.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Paciente::inicializarArchivo() {
    std::ofstream archivo("pacientes.csv", std::ios::app);
    if (archivo.tellp() == 0) {
        archivo << "id,nombre,dni,fecha_ingreso\n";
    }
    archivo.close();
}

void Paciente::registrar() {
    std::ofstream archivo("pacientes.csv", std::ios::app);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de pacientes." << std::endl;
        return;
    }

    std::string nombre, dni, fechaIngreso;
    std::cout << "Ingrese el nombre del paciente: ";
    std::getline(std::cin, nombre);
    std::cout << "Ingrese el DNI del paciente: ";
    std::getline(std::cin, dni);
    std::cout << "Ingrese la fecha de ingreso (YYYY-MM-DD): ";
    std::getline(std::cin, fechaIngreso);

    if (!validarDatos(nombre, dni, fechaIngreso)) {
        std::cerr << "Datos inv�lidos. Intente nuevamente." << std::endl;
        return;
    }

    int id = generarId("pacientes.csv");
    archivo << id << "," << nombre << "," << dni << "," << fechaIngreso << "\n";
    archivo.close();

    std::cout << "Paciente registrado correctamente con ID " << id << "." << std::endl;
}

void Paciente::buscar() {
    std::ifstream archivo("pacientes.csv");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de pacientes." << std::endl;
        return;
    }

    std::string criterio;
    std::cout << "Ingrese el DNI o nombre del paciente a buscar: ";
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
        std::cout << "No se encontraron pacientes con el criterio dado." << std::endl;
    }

    archivo.close();
}

void Paciente::modificar() {
    std::cout << "Funci�n modificar a�n en desarrollo." << std::endl;
}

void Paciente::eliminar() {
    std::cout << "Funci�n eliminar a�n en desarrollo." << std::endl;
}

int Paciente::generarId(const std::string& archivo) {
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

bool Paciente::validarDatos(const std::string& nombre, const std::string& dni, const std::string& fechaIngreso) {
    return !nombre.empty() && dni.size() == 9 && !fechaIngreso.empty();
}
