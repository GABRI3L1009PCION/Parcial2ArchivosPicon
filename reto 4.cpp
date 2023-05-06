#include <iostream>
#include <filesystem>
#include <windows.h>
#include <fstream>
#include <shlobj.h>

using namespace std;
namespace fs = std::filesystem;

void agregarTextoArchivos(int num_files) {
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

    // Crear los archivos y agregarles texto
    for (int i = 1; i <= num_files; i++) {
        fs::path file_path = dir / ("documento" + to_string(i) + ".txt");
        ofstream file(file_path);
        if (file) {
            // Agregar la cantidad de líneas correspondiente al número de archivo
            for (int j = 1; j <= i; j++) {
                file << "Línea " << j << " del documento " << i << endl;
            }
            cout << "Archivo creado y texto agregado: " << file_path << endl;
        } else {
            cerr << "Error al crear el archivo: " << file_path << endl;
        }
        file.close(); // Cerrar el archivo
    }
}

int main() {
    int num_files;
    cout << "¿Cuántos archivos desea crear? ";
    cin >> num_files;
    agregarTextoArchivos(num_files); // Llamada a la función para crear los archivos y agregarles texto
    return 0;
}
