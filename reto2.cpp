#include <iostream>
#include <filesystem>
#include <windows.h>
#include <fstream>

void agregarTextoArchivos() {
    std::string carpeta = "carpeta_de_archivos"; // Ruta de la carpeta donde se guardarán los archivos
    std::filesystem::create_directory(carpeta); // Crear la carpeta si no existe

    for (int i = 1; i <= 10; i++) { // Crear 10 archivos
        std::string nombreArchivo = "documento" + std::to_string(i) + ".txt"; // Nombre del archivo
        std::string rutaArchivo = carpeta + "\\" + nombreArchivo; // Ruta completa del archivo

        std::ofstream archivo(rutaArchivo); // Crear el archivo

        for (int j = 1; j <= i; j++) { // Agregar la cantidad de líneas correspondiente al número de archivo
            archivo << "Línea " << j << " del documento " << i << std::endl;
        }

        archivo.close(); // Cerrar el archivo
    }
}

int main() {
    agregarTextoArchivos();
    return 0;
}
