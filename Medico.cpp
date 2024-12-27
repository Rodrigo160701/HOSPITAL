#include "Medico.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

void Medico::inicializarArchivo() {
    std::ofstream archivo("medicos.csv", std::ios::app);
    if (archivo.tellp() == 0) {
        archivo << "id,nombre,especialidad,dni\n"; // Cabecera del archivo
    }
    archivo.close();
}
bool Medico::validarDNI(const std::string& dni) {
    if (dni.size() != 9) {
        return false;
    }

    std::regex formatoDNI("^\\d{8}[A-Z]$");
    if (!std::regex_match(dni, formatoDNI)) {
        return false;
    }

    const std::string letras = "TRWAGMYFPDXBNJZSQVHLCKE";
    int numeros = std::stoi(dni.substr(0, 8));
    char letraCorrecta = letras[numeros % 23];

    return dni[8] == letraCorrecta;
}

void Medico::registrar() {
    std::ofstream archivo("medicos.csv", std::ios::app);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de m�dicos." << std::endl;
        return;
    }

    std::string nombre, dni, especialidad;
    std::vector<std::string> especialidades = {
        "Cardiolog�a", "Neurolog�a", "Transplante", "Dermatolog�a", "Pediatr�a",
        "Oncolog�a", "Traumatolog�a", "Ginecolog�a", "Urolog�a", "Reumatolog�a",
        "Nefrolog�a", "Hematolog�a", "Otorrinolaringolog�a", "Anestesiolog�a",
        "Gastroenterolog�a", "Medicina General", "Ortopedia", "Psicolog�a",
        "Endocrinolog�a", "Oftalmolog�a"
    };

    std::cout << "Ingrese el nombre del m�dico: ";
    std::getline(std::cin, nombre);
    do {
        std::cout << "Ingrese el DNI del m�dico (8 d�gitos + letra): ";
        std::getline(std::cin, dni);
        if (!validarDNI(dni)) {
            std::cerr << "DNI inv�lido. Debe ser de 8 n�meros seguidos de una letra v�lida." << std::endl;
        }
    } while (!validarDNI(dni));

    int opcion;
    do {
        std::cout << "\nSeleccione la especialidad:\n";
        for (size_t i = 0; i < especialidades.size(); ++i) {
            std::cout << i + 1 << ". " << especialidades[i] << "\n";
        }
        std::cout << "Ingrese el n�mero correspondiente: ";
        std::cin >> opcion;
        std::cin.ignore();

        if (opcion < 1 || opcion > static_cast<int>(especialidades.size())) {
            std::cerr << "Opci�n inv�lida. Intente nuevamente.\n";
        }
        else {
            especialidad = especialidades[opcion - 1];
        }
    } while (opcion < 1 || opcion > static_cast<int>(especialidades.size()));

    if (!validarDatos(nombre, especialidad, dni)) {
        std::cerr << "Datos inv�lidos. Intente nuevamente." << std::endl;
        return;
    }

    int id = generarId("medicos.csv");
    archivo << id << "," << nombre << "," << especialidad << "," << dni << "\n";
    archivo.close();

    std::cout << "M�dico registrado correctamente con ID " << id << "." << std::endl;
}

int Medico::buscar() {
    std::ifstream archivo("medicos.csv");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de m�dicos." << std::endl;
        return -1;
    }

    std::string criterio;
    std::cout << "Ingrese el DNI, nombre o especialidad del m�dico a buscar: ";
    std::getline(std::cin, criterio);

    std::string linea;
    bool encontrado = false;
    int medicoId = -1;

    while (std::getline(archivo, linea)) {
        if (linea.empty() || linea.find("id") == 0) {
            continue; // Ignora l�neas vac�as o la cabecera
        }

        if (linea.find(criterio) != std::string::npos) {
            std::cout << linea << std::endl;
            std::stringstream ss(linea);
            std::string idStr;
            std::getline(ss, idStr, ',');
            medicoId = std::stoi(idStr);
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron m�dicos con el criterio dado." << std::endl;
    }

    archivo.close();
    return medicoId;
}

void Medico::menuMedicoSeleccionado(int medicoId) {
    int opcion;
    do {
        std::cout << "\n--- Men� M�dico Seleccionado ---\n";
        std::cout << "1. Modificar M�dico\n";
        std::cout << "2. Eliminar M�dico\n";
        std::cout << "0. Volver al Men� M�dico\n";
        std::cout << "Seleccione una opci�n: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            modificar(medicoId);
            break;
        case 2:
            eliminar(medicoId);
            break;
        case 0:
            std::cout << "Volviendo al Men� M�dico..." << std::endl;
            break;
        default:
            std::cout << "Opci�n no v�lida. Intente nuevamente." << std::endl;
        }
    } while (opcion != 0);
}

void Medico::modificar(int medicoId) {
    std::ifstream archivoEntrada("medicos.csv");
    if (!archivoEntrada) {
        std::cerr << "Error al abrir el archivo de m�dicos." << std::endl;
        return;
    }

    std::ofstream archivoTemporal("medicos_temp.csv");
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
        std::string idStr, nombre, especialidad, dni;
        std::getline(ss, idStr, ',');

        if (std::stoi(idStr) == medicoId) {
            encontrado = true;
            std::cout << "M�dico encontrado: " << linea << std::endl;

            std::cout << "Ingrese el nuevo nombre del m�dico (deje vac�o para no modificar): ";
            std::string nuevoNombre;
            std::getline(std::cin, nuevoNombre);
            if (!nuevoNombre.empty()) nombre = nuevoNombre;

            int opcion;
            std::vector<std::string> especialidades = {
                "Cardiolog�a", "Neurolog�a", "Transplante", "Dermatolog�a", "Pediatr�a",
                "Oncolog�a", "Traumatolog�a", "Ginecolog�a", "Urolog�a", "Reumatolog�a",
                "Nefrolog�a", "Hematolog�a", "Otorrinolaringolog�a", "Anestesiolog�a",
                "Gastroenterolog�a", "Medicina General", "Ortopedia", "Psicolog�a",
                "Endocrinolog�a", "Oftalmolog�a"
            };

            do {
                std::cout << "\nSeleccione la nueva especialidad (deje vac�o para no modificar):\n";
                for (size_t i = 0; i < especialidades.size(); ++i) {
                    std::cout << i + 1 << ". " << especialidades[i] << "\n";
                }
                std::cout << "Ingrese el n�mero correspondiente o presione Enter para no modificar: ";
                std::string input;
                std::getline(std::cin, input);
                if (input.empty()) break;
                opcion = std::stoi(input);
                if (opcion >= 1 && opcion <= static_cast<int>(especialidades.size())) {
                    especialidad = especialidades[opcion - 1];
                }
                else {
                    std::cerr << "Opci�n inv�lida.\n";
                }
            } while (opcion < 1 || opcion > static_cast<int>(especialidades.size()));

            std::cout << "Ingrese el nuevo DNI del m�dico (deje vac�o para no modificar): ";
            std::string nuevoDni;
            std::getline(std::cin, nuevoDni);
            if (!nuevoDni.empty() && validarDNI(nuevoDni)) dni = nuevoDni;
            else if (!nuevoDni.empty()) std::cerr << "DNI inv�lido. No se modific�." << std::endl;

            archivoTemporal << idStr << "," << nombre << "," << especialidad << "," << dni << "\n";
            std::cout << "M�dico modificado correctamente." << std::endl;
        }
        else {
            archivoTemporal << linea << "\n";
        }
    }

    if (!encontrado) {
        std::cout << "No se encontr� ning�n m�dico con el ID proporcionado." << std::endl;
    }

    archivoEntrada.close();
    archivoTemporal.close();

    if (std::remove("medicos.csv") == 0) {
        std::cout << "Archivo original eliminado correctamente." << std::endl;
    }
    else {
        std::cerr << "Advertencia: No se pudo eliminar el archivo original (puede que no exista)." << std::endl;
    }

    if (std::rename("medicos_temp.csv", "medicos.csv") != 0) {
        perror("Error al renombrar el archivo temporal");
    }
}

void Medico::eliminar(int medicoId) {
    std::ifstream archivoEntrada("medicos.csv");
    if (!archivoEntrada) {
        std::cerr << "Error al abrir el archivo de m�dicos." << std::endl;
        return;
    }

    std::ofstream archivoTemporal("medicos_temp.csv");
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

        if (std::stoi(idStr) == medicoId) {
            encontrado = true;
            std::cout << "M�dico eliminado: " << linea << std::endl;
        }
        else {
            archivoTemporal << linea << "\n";
        }
    }

    if (!encontrado) {
        std::cout << "No se encontr� ning�n m�dico con el ID proporcionado." << std::endl;
    }

    archivoEntrada.close();
    archivoTemporal.close();

    if (std::remove("medicos.csv") == 0) {
        std::cout << "Archivo original eliminado correctamente." << std::endl;
    }
    else {
        std::cerr << "Advertencia: No se pudo eliminar el archivo original (puede que no exista)." << std::endl;
    }

    if (std::rename("medicos_temp.csv", "medicos.csv") != 0) {
        perror("Error al renombrar el archivo temporal");
    }
}

int Medico::generarId(const std::string& archivo) {
    std::ifstream entrada(archivo);
    std::string linea;
    int ultimoId = 0;

    while (std::getline(entrada, linea)) {
        if (linea.empty() || linea.find("id") == 0) continue;

        std::stringstream ss(linea);
        std::string id;
        std::getline(ss, id, ',');
        if (!id.empty()) {
            ultimoId = std::stoi(id);
        }
    }

    return ultimoId + 1;
}

bool Medico::validarDatos(const std::string& nombre, const std::string& especialidad, const std::string& dni) {
    return !nombre.empty() && !especialidad.empty() && dni.size() == 9;
}
