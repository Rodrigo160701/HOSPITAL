#include "Paciente.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

void Paciente::inicializarArchivo() {
    std::ofstream archivo("pacientes.csv", std::ios::app);
    if (archivo.tellp() == 0) {
        archivo << "id,nombre,dni,fecha_ingreso,historial_clinico\n"; // Cabecera del archivo
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

    do {
        std::cout << "Ingrese la fecha de ingreso del paciente (YYYY-MM-DD): ";
        std::getline(std::cin, fechaIngreso);
        if (!validarFecha(fechaIngreso)) {
            std::cerr << "Fecha inválida. Asegúrese de usar el formato YYYY-MM-DD y que sea una fecha válida." << std::endl;
        }
    } while (!validarFecha(fechaIngreso));

    if (!validarDatos(nombre, dni, fechaIngreso)) {
        std::cerr << "Datos inválidos. Intente nuevamente." << std::endl;
        return;
    }

    int id = generarId("pacientes.csv");
    archivo << id << "," << nombre << "," << dni << "," << fechaIngreso << ",\n"; // Historial vacío
    archivo.close();

    std::cout << "Paciente registrado correctamente con ID " << id << "." << std::endl;
}

int Paciente::buscar() {
    std::ifstream archivo("pacientes.csv");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de pacientes." << std::endl;
        return -1;
    }

    std::string criterio;
    std::cout << "Ingrese el DNI, nombre o fecha de ingreso del paciente a buscar: ";
    std::getline(std::cin, criterio);

    std::string linea;
    bool encontrado = false;
    int pacienteId = -1;

    while (std::getline(archivo, linea)) {
        if (linea.empty() || linea.find("id") == 0) {
            continue; // Ignora líneas vacías o la cabecera
        }

        if (linea.find(criterio) != std::string::npos) {
            std::cout << linea << std::endl;
            std::stringstream ss(linea);
            std::string idStr;
            std::getline(ss, idStr, ',');
            pacienteId = std::stoi(idStr); // Conversión segura porque ya validamos
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron pacientes con el criterio dado." << std::endl;
    }

    archivo.close();
    return pacienteId;
}

void Paciente::menuPacienteSeleccionado(int pacienteId) {
    int opcion;
    do {
        std::cout << "\n--- Menú Paciente Seleccionado ---\n";
        std::cout << "1. Modificar Paciente\n";
        std::cout << "2. Eliminar Paciente\n";
        std::cout << "3. Agregar Historial Clínico\n";
        std::cout << "0. Volver al Menú Paciente\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            modificar(pacienteId);
            break;
        case 2:
            eliminar(pacienteId);
            break;
        case 3:
            agregarHistorialClinico(pacienteId);
            break;
        case 0:
            std::cout << "Volviendo al Menú Paciente..." << std::endl;
            break;
        default:
            std::cout << "Opción no válida. Intente nuevamente." << std::endl;
        }
    } while (opcion != 0);
}

void Paciente::modificar(int pacienteId) {
    std::ifstream archivoEntrada("pacientes.csv");
    if (!archivoEntrada) {
        std::cerr << "Error al abrir el archivo de pacientes." << std::endl;
        return;
    }

    std::ofstream archivoTemporal("pacientes_temp.csv");
    if (!archivoTemporal) {
        std::cerr << "Error al crear el archivo temporal." << std::endl;
        return;
    }

    std::string linea;
    bool encontrado = false;

    while (std::getline(archivoEntrada, linea)) {
        if (linea.empty() || linea.find("id") == 0) {
            archivoTemporal << linea << "\n"; // Copia la cabecera
            continue;
        }

        std::stringstream ss(linea);
        std::string idStr, nombre, dni, fechaIngreso, historial;
        std::getline(ss, idStr, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, dni, ',');
        std::getline(ss, fechaIngreso, ',');
        std::getline(ss, historial);

        if (std::stoi(idStr) == pacienteId) {
            encontrado = true;
            std::cout << "Paciente encontrado: " << linea << std::endl;

            std::cout << "Ingrese el nuevo nombre del paciente (deje vacío para no modificar): ";
            std::string nuevoNombre;
            std::getline(std::cin, nuevoNombre);
            if (!nuevoNombre.empty()) nombre = nuevoNombre;

            std::cout << "Ingrese el nuevo DNI del paciente (deje vacío para no modificar): ";
            std::string nuevoDni;
            std::getline(std::cin, nuevoDni);
            if (!nuevoDni.empty()) dni = nuevoDni;

            std::cout << "Ingrese la nueva fecha de ingreso del paciente (deje vacío para no modificar): ";
            std::string nuevaFechaIngreso;
            std::getline(std::cin, nuevaFechaIngreso);
            if (!nuevaFechaIngreso.empty() && validarFecha(nuevaFechaIngreso)) fechaIngreso = nuevaFechaIngreso;
            else if (!nuevaFechaIngreso.empty()) std::cerr << "Fecha inválida. No se modificó la fecha." << std::endl;

            archivoTemporal << idStr << "," << nombre << "," << dni << "," << fechaIngreso << "," << historial << "\n";
            std::cout << "Paciente modificado correctamente." << std::endl;
        }
        else {
            archivoTemporal << linea << "\n";
        }
    }

    if (!encontrado) {
        std::cout << "No se encontró ningún paciente con el ID proporcionado." << std::endl;
    }

    archivoEntrada.close();
    archivoTemporal.close();

    // Verificar si el archivo destino ya existe y eliminarlo
    if (std::remove("pacientes.csv") == 0) {
        std::cout << "Archivo original eliminado correctamente." << std::endl;
    }
    else {
        std::cerr << "Advertencia: No se pudo eliminar el archivo original (puede que no exista)." << std::endl;
    }

    if (std::rename("pacientes_temp.csv", "pacientes.csv") != 0) {
        perror("Error al renombrar el archivo temporal");
    }
}

void Paciente::eliminar(int pacienteId) {
    std::ifstream archivoEntrada("pacientes.csv");
    if (!archivoEntrada) {
        std::cerr << "Error al abrir el archivo de pacientes." << std::endl;
        return;
    }

    std::ofstream archivoTemporal("pacientes_temp.csv");
    if (!archivoTemporal) {
        std::cerr << "Error al crear el archivo temporal." << std::endl;
        return;
    }

    std::string linea;
    bool encontrado = false;

    while (std::getline(archivoEntrada, linea)) {
        if (linea.empty() || linea.find("id") == 0) {
            archivoTemporal << linea << "\n"; // Copia la cabecera
            continue;
        }

        std::stringstream ss(linea);
        std::string idStr;
        std::getline(ss, idStr, ',');

        if (std::stoi(idStr) == pacienteId) {
            encontrado = true;
            std::cout << "Paciente eliminado: " << linea << std::endl;
        }
        else {
            archivoTemporal << linea << "\n";
        }
    }

    if (!encontrado) {
        std::cout << "No se encontró ningún paciente con el ID proporcionado." << std::endl;
    }

    archivoEntrada.close();
    archivoTemporal.close();

    // Verificar si el archivo destino ya existe y eliminarlo
    if (std::remove("pacientes.csv") == 0) {
        std::cout << "Archivo original eliminado correctamente." << std::endl;
    }
    else {
        std::cerr << "Advertencia: No se pudo eliminar el archivo original (puede que no exista)." << std::endl;
    }

    if (std::rename("pacientes_temp.csv", "pacientes.csv") != 0) {
        perror("Error al renombrar el archivo temporal");
    }
}

void Paciente::agregarHistorialClinico(int pacienteId) {
    std::ifstream archivoEntrada("pacientes.csv");
    if (!archivoEntrada) {
        std::cerr << "Error al abrir el archivo de pacientes." << std::endl;
        return;
    }

    std::ofstream archivoTemporal("pacientes_temp.csv");
    if (!archivoTemporal) {
        std::cerr << "Error al crear el archivo temporal." << std::endl;
        return;
    }

    std::string linea;
    bool encontrado = false;

    while (std::getline(archivoEntrada, linea)) {
        if (linea.empty() || linea.find("id") == 0) {
            archivoTemporal << linea << "\n"; // Copia la cabecera
            continue;
        }

        std::stringstream ss(linea);
        std::string idStr, nombre, dni, fechaIngreso, historial;
        std::getline(ss, idStr, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, dni, ',');
        std::getline(ss, fechaIngreso, ',');
        std::getline(ss, historial);

        if (std::stoi(idStr) == pacienteId) {
            encontrado = true;
            std::cout << "Paciente encontrado: " << linea << std::endl;

            std::cout << "Ingrese el historial clínico a agregar: ";
            std::string nuevoHistorial;
            std::getline(std::cin, nuevoHistorial);
            historial += " | " + nuevoHistorial;

            archivoTemporal << idStr << "," << nombre << "," << dni << "," << fechaIngreso << "," << historial << "\n";
            std::cout << "Historial clínico agregado correctamente." << std::endl;
        }
        else {
            archivoTemporal << linea << "\n";
        }
    }

    if (!encontrado) {
        std::cout << "No se encontró ningún paciente con el ID proporcionado." << std::endl;
    }

    archivoEntrada.close();
    archivoTemporal.close();

    // Verificar si el archivo destino ya existe y eliminarlo
    if (std::remove("pacientes.csv") == 0) {
        std::cout << "Archivo original eliminado correctamente." << std::endl;
    }
    else {
        std::cerr << "Advertencia: No se pudo eliminar el archivo original (puede que no exista)." << std::endl;
    }

    if (std::rename("pacientes_temp.csv", "pacientes.csv") != 0) {
        perror("Error al renombrar el archivo temporal");
    }
}

int Paciente::generarId(const std::string& archivo) {
    std::ifstream entrada(archivo);
    std::string linea;
    int ultimoId = 0;

    while (std::getline(entrada, linea)) {
        if (linea.empty() || linea.find("id") == 0) continue; // Ignora líneas vacías o la cabecera

        std::stringstream ss(linea);
        std::string id;
        std::getline(ss, id, ',');
        if (!id.empty()) {
            ultimoId = std::stoi(id);
        }
    }

    return ultimoId + 1;
}

bool Paciente::validarDatos(const std::string& nombre, const std::string& dni, const std::string& fechaIngreso) {
    return !nombre.empty() && dni.size() == 9 && validarFecha(fechaIngreso);
}

bool Paciente::validarFecha(const std::string& fecha) {
    std::regex formatoFecha("^(\\d{4})-(\\d{2})-(\\d{2})$");
    std::smatch coincidencia;

    if (!std::regex_match(fecha, coincidencia, formatoFecha)) {
        return false;
    }

    int anio = std::stoi(coincidencia[1].str());
    int mes = std::stoi(coincidencia[2].str());
    int dia = std::stoi(coincidencia[3].str());

    if (mes < 1 || mes > 12) {
        return false;
    }

    int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Comprobar años bisiestos
    if (mes == 2 && ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))) {
        diasPorMes[1] = 29;
    }

    return dia >= 1 && dia <= diasPorMes[mes - 1];
}
