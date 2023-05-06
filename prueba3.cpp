#include <iostream>
#include <fstream>
#include <filesystem>
#include <windows.h>
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
        fs::path file_path = dir / ("documento" + to_string(i));
        if (fs::exists(file_path)) {
            // El archivo ya existe, eliminarlo
            fs::remove(file_path);
        }
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
