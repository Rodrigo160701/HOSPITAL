#ifndef BACKUP_H
#define BACKUP_H

#include <string>

class Backup {
public:
    static void menuBackup();
    static void backupPacientes();
    static void backupMedicos();
    static void backupCitas();
    static void backupServicios();
    static void backupTodo();

private:
    static std::string crearCarpetaBackup();
    static void copiarArchivo(const std::string& origen, const std::string& destino);
};

#endif
