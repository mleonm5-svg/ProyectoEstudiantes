#include <iostream>
#include <vector>
#include <map>
#include <windows.h>

#include "MySQLConexion.h"
#include "EloquentORM.h"

using namespace std;

// FUNCION PARA COLORES
void color(int colorCodigo) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCodigo);
}

// MOSTRAR ESTUDIANTES
void mostrar_estudiantes(EloquentORM &estudiantes) {

    vector<map<string, string>> lista = estudiantes.getAll();

    color(11);
    cout << "\n===== LISTA DE ESTUDIANTES =====\n";
    color(7);

    for (auto &reg : lista) {

        cout << "ID: " << reg["id"]
             << " | Nombre: " << reg["nombre"]
             << " | Carnet: " << reg["carnet"]
             << " | Edad: " << reg["edad"]
             << " | Correo: " << reg["correo"]
             << endl;
    }
}

// AGREGAR ESTUDIANTE
void agregar_estudiante(MySQLConexion &conexion) {

    string nombre, carnet, edad, correo;

    cin.ignore();

    cout << "\nNombre: ";
    getline(cin, nombre);

    cout << "Carnet: ";
    getline(cin, carnet);

    cout << "Edad: ";
    getline(cin, edad);

    cout << "Correo: ";
    getline(cin, correo);

    string sql =
        "INSERT INTO estudiantes(nombre, carnet, edad, correo) VALUES ('" +
        nombre + "', '" +
        carnet + "', " +
        edad + ", '" +
        correo + "')";

    conexion.executeQuery(sql);

    color(10);
    cout << "\nEstudiante agregado correctamente.\n";
    color(7);
}

// ACTUALIZAR ESTUDIANTE
void actualizar_estudiante(MySQLConexion &conexion) {

    string id, nombre, carnet, edad, correo;

    cout << "\nIngrese ID del estudiante a actualizar: ";
    cin >> id;

    cin.ignore();

    cout << "Nuevo nombre: ";
    getline(cin, nombre);

    cout << "Nuevo carnet: ";
    getline(cin, carnet);

    cout << "Nueva edad: ";
    getline(cin, edad);

    cout << "Nuevo correo: ";
    getline(cin, correo);

    string sql =
        "UPDATE estudiantes SET nombre='" + nombre +
        "', carnet='" + carnet +
        "', edad=" + edad +
        ", correo='" + correo +
        "' WHERE id=" + id;

    conexion.executeQuery(sql);

    color(14);
    cout << "\nEstudiante actualizado correctamente.\n";
    color(7);
}

// ELIMINAR ESTUDIANTE
void eliminar_estudiante(MySQLConexion &conexion) {

    string id;

    cout << "\nIngrese ID del estudiante a eliminar: ";
    cin >> id;

    // ELIMINAR INSCRIPCIONES RELACIONADAS
    string sqlInscripciones =
        "DELETE FROM inscripciones WHERE estudiante_id=" + id;

    conexion.executeQuery(sqlInscripciones);

    // ELIMINAR ESTUDIANTE
    string sqlEstudiante =
        "DELETE FROM estudiantes WHERE id=" + id;

    conexion.executeQuery(sqlEstudiante);

    color(12);
    cout << "\nEstudiante eliminado correctamente.\n";
    color(7);
}

int main() {

    // CONEXION MYSQL
    MySQLConexion conexion(
        "root",
        "Maynor1234",
        "proyecto_estudiantes",
        "127.0.0.1",
        3306
    );

    if (!conexion.open()) {

        color(12);
        cerr << "Error al conectar con MySQL" << endl;
        color(7);

        return 1;
    }

    color(10);
    cout << "Conexion exitosa a MySQL\n";
    color(7);

    // COLUMNAS TABLA ESTUDIANTES
    vector<string> columnasEstudiantes = {
        "id",
        "nombre",
        "carnet",
        "edad",
        "correo"
    };

    // ORM
    EloquentORM estudiantes(
        conexion,
        "estudiantes",
        columnasEstudiantes
    );

    int opcion;

    do {

        color(11);
        cout << "\n===== SISTEMA DE ESTUDIANTES =====\n";
        color(7);

        cout << "1. Mostrar estudiantes\n";
        cout << "2. Agregar estudiante\n";
        cout << "3. Actualizar estudiante\n";
        cout << "4. Eliminar estudiante\n";
        cout << "5. Salir\n";

        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {

            case 1:
                mostrar_estudiantes(estudiantes);
                break;

            case 2:
                agregar_estudiante(conexion);
                break;

            case 3:
                actualizar_estudiante(conexion);
                break;

            case 4:
                eliminar_estudiante(conexion);
                break;

            case 5:

                color(14);
                cout << "\nSaliendo del sistema...\n";
                color(7);

                break;

            default:

                color(12);
                cout << "\nOpcion invalida.\n";
                color(7);
        }

    } while (opcion != 5);

    return 0;
}