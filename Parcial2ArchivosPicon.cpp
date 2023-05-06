//*
#include <iostream>
#include <filesystem>
#include <windows.h>
#include <fstream>
#include <shlobj.h>

using namespace std;
namespace fs = std::filesystem;

void create_files(int num_files) {
    // Obtener el directorio de Mis Documentos
    wchar_t documents_path[MAX_PATH];
    if (SHGetFolderPathW(NULL, CSIDL_MYDOCUMENTS, NULL, 0, documents_path) != S_OK) {
        cerr << "Error al obtener el directorio de Mis Documentos" << endl;
        return;
    }
    fs::path documents_dir(documents_path);

    // Obtener el directorio de Escritorio
    wchar_t desktop_path[MAX_PATH];
    if (SHGetFolderPathW(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, desktop_path) != S_OK) {
        cerr << "Error al obtener el directorio de Escritorio" << endl;
        return;
    }
    fs::path desktop_dir(desktop_path);

    // Elegir el directorio según la cantidad de archivos
    fs::path dir;
    if (num_files % 2 == 0) {
        dir = documents_dir / "par";
    } else {
        dir = desktop_dir / "impar";
    }

    // Crear la carpeta si no existe
    if (!fs::exists(dir)) {
        fs::create_directory(dir);
    }

    // Crear los archivos
    for (int i = 1; i <= num_files; i++) {
        fs::path file_path = dir / ("documento" + to_string(i) + ".txt");
        ofstream file(file_path);
        if (file) {
            cout << "Archivo creado: " << file_path << endl;
        } else {
            cerr << "Error al crear el archivo: " << file_path << endl;
        }
    }
}

int main() {
    int num_files;
    cout << "¿Cuántos archivos desea crear? ";
    cin >> num_files;
    create_files(num_files);
    return 0;
}
*//
//* ejercio 8  solo la funcion
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
*//
//* ejercicio 9 combinado con el primero

#include <iostream>
#include <filesystem>
#include <windows.h>
#include <fstream>
#include <shlobj.h>
#include <ctime>
using namespace std;
namespace fs = std::filesystem;

void create_files(int num_files) {
    // Obtener el directorio de Mis Documentos
    wchar_t documents_path[MAX_PATH];
    if (SHGetFolderPathW(NULL, CSIDL_MYDOCUMENTS, NULL, 0, documents_path) != S_OK) {
        cerr << "Error al obtener el directorio de Mis Documentos" << endl;
        return;
    }
    fs::path documents_dir(documents_path);

    // Obtener el directorio de Escritorio
    wchar_t desktop_path[MAX_PATH];
    if (SHGetFolderPathW(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, desktop_path) != S_OK) {
        cerr << "Error al obtener el directorio de Escritorio" << endl;
        return;
    }
    fs::path desktop_dir(desktop_path);

    // Elegir el directorio según la cantidad de archivos
    fs::path dir;
    if (num_files % 2 == 0) {
        dir = documents_dir / "par";
    } else {
        dir = desktop_dir / "impar";
    }

    // Crear la carpeta si no existe
    if (!fs::exists(dir)) {
        fs::create_directory(dir);
    }

    // Crear los archivos
    for (int i = 1; i <= num_files; i++) {
        fs::path file_path = dir / ("documento" + to_string(i) + ".txt");
        ofstream file(file_path);
        if (file) {
            cout << "Archivo creado: " << file_path << endl;
        } else {
            cerr << "Error al crear el archivo: " << file_path << endl;
        }
    }
}

fs::path find_smallest_file(const fs::path& folder_path) {
    fs::path smallest_file;
    uintmax_t smallest_size = std::numeric_limits<uintmax_t>::max();
    for (const auto& entry : fs::directory_iterator(folder_path)) {
        if (entry.is_regular_file()) {
            uintmax_t file_size = entry.file_size();
            if (file_size < smallest_size) {
                smallest_file = entry.path();
                smallest_size = file_size;
            }
        }
    }
    return smallest_file;
}

int main() {
    int num_files;
    cout << "¿Cuántos archivos desea crear? ";
    cin >> num_files;
    create_files(num_files);

    // Buscar el archivo más pequeño en la carpeta creada
    fs::path smallest_file = find_smallest_file(fs::current_path() / "impar");

    if (!smallest_file.empty()) {
        cout << "El archivo más pequeño es: " << smallest_file << endl;
    } else {
        cerr << "No se encontraron archivos en la carpeta" << endl;
    }

    return 0;
}
*//