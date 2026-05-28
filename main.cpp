#include <iostream>
#include <vector>
#include <map>

#include "MySQLConexion.h"
#include "EloquentORM.h"

using namespace std;

void mostrar_estudiantes(EloquentORM &estudiantes) {

    vector<map<string, string>> lista = estudiantes.getAll();

    cout << "\n===== LISTA DE ESTUDIANTES =====\n";

    for (auto &reg : lista) {

        cout << "ID: " << reg["id"]
             << " | Nombre: " << reg["nombre"]
             << " | Carnet: " << reg["carnet"]
             << " | Edad: " << reg["edad"]
             << " | Correo: " << reg["correo"]
             << endl;
    }
}

int main() {

    MySQLConexion conexion(
        "root",
        "Maynor1234",
        "proyecto_estudiantes",
        "127.0.0.1",
        3306
    );

    if (!conexion.open()) {

        cerr << "Error al conectar con MySQL" << endl;
        return 1;
    }

    cout << "Conexion exitosa a MySQL\n";

    vector<string> columnasEstudiantes = {
        "id",
        "nombre",
        "carnet",
        "edad",
        "correo"
    };

    EloquentORM estudiantes(
        conexion,
        "estudiantes",
        columnasEstudiantes
    );

    mostrar_estudiantes(estudiantes);

    return 0;
}