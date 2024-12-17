#include "Cita.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

void Cita::inicializarArchivo() {
    std::ofstream archivo("citas.csv", std::ios::app);
    if (archivo.tellp() == 0) {
        archivo << "id_cita,paciente_id,medico_id,fecha,urgencia\n";
    }
    archivo.close();
}

bool Cita::validarFecha(const std::string& fecha) {
    std::regex formatoFecha("\\d{4}-\\d{2}-\\d{2}");
    if (!std::regex_match(fecha, formatoFecha)) {
        return false;
    }

    std::istringstream ss(fecha);
    int anio, mes, dia;
    char separador1, separador2;
    ss >> anio >> separador1 >> mes >> separador2 >> dia;

    if (separador1 != '-' || separador2 != '-' || mes < 1 || mes > 12 || dia < 1 || dia > 31) {
        return false;
    }

    if (mes == 2) {
        bool esBisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
        return dia <= (esBisiesto ? 29 : 28);
    }

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        return dia <= 30;
    }

    return true;
}

void Cita::asignar() {
    std::ofstream archivo("citas.csv", std::ios::app);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de citas." << std::endl;
        return;
    }

    int pacienteId, medicoId, urgencia;
    std::string fecha;
    std::cout << "Ingrese el ID del paciente: ";
    std::cin >> pacienteId;
    std::cin.ignore();
    std::cout << "Ingrese el ID del médico: ";
    std::cin >> medicoId;
    std::cin.ignore();

    do {
        std::cout << "Ingrese la fecha de la cita (YYYY-MM-DD): ";
        std::getline(std::cin, fecha);
        if (!validarFecha(fecha)) {
            std::cerr << "Fecha inválida. Intente nuevamente." << std::endl;
        }
    } while (!validarFecha(fecha));

    std::cout << "Ingrese el nivel de urgencia (1-5): ";
    std::cin >> urgencia;
    std::cin.ignore();

    if (!validarDatos(fecha, urgencia, pacienteId, medicoId)) {
        std::cerr << "Datos inválidos. Intente nuevamente." << std::endl;
        return;
    }

    int id = generarId("citas.csv");
    archivo << id << "," << pacienteId << "," << medicoId << "," << fecha << "," << urgencia << "\n";
    archivo.close();

    std::cout << "Cita asignada correctamente con ID " << id << "." << std::endl;
}

int Cita::buscar() {
    std::ifstream archivo("citas.csv");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de citas." << std::endl;
        return -1;
    }

    std::string criterio;
    std::cout << "Ingrese el ID de cita, fecha, paciente o médico a buscar: ";
    std::getline(std::cin, criterio);

    std::string linea;
    bool encontrado = false;
    int citaId = -1;

    while (std::getline(archivo, linea)) {
        if (linea.find(criterio) != std::string::npos) {
            std::cout << linea << std::endl;
            std::stringstream ss(linea);
            std::string idStr;
            std::getline(ss, idStr, ',');
            citaId = std::stoi(idStr);
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron citas con el criterio dado." << std::endl;
    }

    archivo.close();
    return citaId;
}

void Cita::menuCitaSeleccionada(int citaId) {
    int opcion;
    do {
        std::cout << "\n--- Menú Cita Seleccionada ---\n";
        std::cout << "1. Modificar Cita\n";
        std::cout << "2. Cancelar Cita\n";
        std::cout << "0. Volver al Menú Cita\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            modificar(citaId);
            break;
        case 2:
            cancelar(citaId);
            break;
        case 0:
            std::cout << "Volviendo al Menú Cita..." << std::endl;
            break;
        default:
            std::cout << "Opción no válida. Intente nuevamente." << std::endl;
        }
    } while (opcion != 0);
}

void Cita::modificar(int citaId) {
    std::ifstream archivoEntrada("citas.csv");
    if (!archivoEntrada) {
        std::cerr << "Error al abrir el archivo de citas." << std::endl;
        return;
    }

    std::ofstream archivoTemporal("citas_temp.csv");
    if (!archivoTemporal) {
        std::cerr << "Error al crear el archivo temporal." << std::endl;
        return;
    }

    std::string linea;
    bool encontrado = false;

    while (std::getline(archivoEntrada, linea)) {
        if (linea.empty() || linea.find("id_cita") == 0) {
            archivoTemporal << linea << "\n"; 
            continue;
        }

        std::stringstream ss(linea);
        std::string idStr, pacienteId, medicoId, fecha, urgenciaStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, pacienteId, ',');
        std::getline(ss, medicoId, ',');
        std::getline(ss, fecha, ',');
        std::getline(ss, urgenciaStr);

        if (std::stoi(idStr) == citaId) {
            encontrado = true;
            std::cout << "Cita encontrada: " << linea << std::endl;

            std::string nuevaFecha;
            do {
                std::cout << "Ingrese la nueva fecha de la cita (deje vacío para no modificar): ";
                std::getline(std::cin, nuevaFecha);
                if (!nuevaFecha.empty() && !validarFecha(nuevaFecha)) {
                    std::cerr << "Fecha inválida. Intente nuevamente." << std::endl;
                    nuevaFecha.clear();
                }
            } while (!nuevaFecha.empty() && !validarFecha(nuevaFecha));
            if (!nuevaFecha.empty()) fecha = nuevaFecha;

            std::cout << "Ingrese el nuevo nivel de urgencia (deje vacío para no modificar): ";
            std::string nuevaUrgenciaStr;
            std::getline(std::cin, nuevaUrgenciaStr);
            if (!nuevaUrgenciaStr.empty()) urgenciaStr = nuevaUrgenciaStr;

            archivoTemporal << idStr << "," << pacienteId << "," << medicoId << "," << fecha << "," << urgenciaStr << "\n";
            std::cout << "Cita modificada correctamente." << std::endl;
        }
        else {
            archivoTemporal << linea << "\n";
        }
    }

    if (!encontrado) {
        std::cout << "No se encontró ninguna cita con el ID proporcionado." << std::endl;
    }

    archivoEntrada.close();
    archivoTemporal.close();

        if (std::remove("citas.csv") == 0) {
        std::cout << "Archivo original eliminado correctamente." << std::endl;
    }
    else {
        std::cerr << "Advertencia: No se pudo eliminar el archivo original (puede que no exista)." << std::endl;
    }

    if (std::rename("citas_temp.csv", "citas.csv") != 0) {
        perror("Error al renombrar el archivo temporal");
    }
}

void Cita::cancelar(int citaId) {
    std::ifstream archivoEntrada("citas.csv");
    if (!archivoEntrada) {
        std::cerr << "Error al abrir el archivo de citas." << std::endl;
        return;
    }

    std::ofstream archivoTemporal("citas_temp.csv");
    if (!archivoTemporal) {
        std::cerr << "Error al crear el archivo temporal." << std::endl;
        return;
    }

    std::string linea;
    bool encontrado = false;

    while (std::getline(archivoEntrada, linea)) {
        if (linea.empty() || linea.find("id_cita") == 0) {
            archivoTemporal << linea << "\n"; 
            continue;
        }

        std::stringstream ss(linea);
        std::string idStr;
        std::getline(ss, idStr, ',');

        if (std::stoi(idStr) == citaId) {
            encontrado = true;
            std::cout << "Cita cancelada: " << linea << std::endl;
        }
        else {
            archivoTemporal << linea << "\n";
        }
    }

    if (!encontrado) {
        std::cout << "No se encontró ninguna cita con el ID proporcionado." << std::endl;
    }

    archivoEntrada.close();
    archivoTemporal.close();

    
    if (std::remove("citas.csv") == 0) {
        std::cout << "Archivo original eliminado correctamente." << std::endl;
    }
    else {
        std::cerr << "Advertencia: No se pudo eliminar el archivo original (puede que no exista)." << std::endl;
    }

    if (std::rename("citas_temp.csv", "citas.csv") != 0) {
        perror("Error al renombrar el archivo temporal");
    }
}

int Cita::generarId(const std::string& archivo) {
    std::ifstream entrada(archivo);
    std::string linea;
    int ultimoId = 0;

    while (std::getline(entrada, linea)) {
        std::stringstream ss(linea);
        std::string id;
        std::getline(ss, id, ',');
        if (!id.empty() && id != "id_cita") {
            ultimoId = std::stoi(id);
        }
    }

    return ultimoId + 1;
}

bool Cita::validarDatos(const std::string& fecha, int urgencia, int pacienteId, int medicoId) {
    return validarFecha(fecha) && urgencia >= 1 && urgencia <= 5 && pacienteId > 0 && medicoId > 0;
}
