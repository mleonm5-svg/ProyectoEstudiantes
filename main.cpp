#include <iostream>
#include <vector>
#include <map>
#include <windows.h>

#include "MySQLConexion.h"
#include "EloquentORM.h"

using namespace std;

void color(int colorCodigo) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCodigo);
}

// ================= ESTUDIANTES =================

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
             << " | Correo: " << reg["correo"] << endl;
    }
}

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

    string sql = "INSERT INTO estudiantes(nombre, carnet, edad, correo) VALUES ('" +
                 nombre + "', '" + carnet + "', " + edad + ", '" + correo + "')";

    conexion.executeQuery(sql);

    color(10);
    cout << "\nEstudiante agregado correctamente.\n";
    color(7);
}

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

    string sql = "UPDATE estudiantes SET nombre='" + nombre +
                 "', carnet='" + carnet +
                 "', edad=" + edad +
                 ", correo='" + correo +
                 "' WHERE id=" + id;

    conexion.executeQuery(sql);

    color(14);
    cout << "\nEstudiante actualizado correctamente.\n";
    color(7);
}

void eliminar_estudiante(MySQLConexion &conexion) {
    string id;

    cout << "\nIngrese ID del estudiante a eliminar: ";
    cin >> id;

    conexion.executeQuery("DELETE FROM inscripciones WHERE estudiante_id=" + id);
    conexion.executeQuery("DELETE FROM estudiantes WHERE id=" + id);

    color(12);
    cout << "\nEstudiante eliminado correctamente.\n";
    color(7);
}

// ================= CURSOS =================

void mostrar_cursos(EloquentORM &cursos) {
    vector<map<string, string>> lista = cursos.getAll();

    color(11);
    cout << "\n===== LISTA DE CURSOS =====\n";
    color(7);

    for (auto &reg : lista) {
        cout << "ID: " << reg["id"]
             << " | Nombre: " << reg["nombre"]
             << " | Codigo: " << reg["codigo"]
             << " | Creditos: " << reg["creditos"] << endl;
    }
}

void agregar_curso(MySQLConexion &conexion) {
    string nombre, codigo, creditos;
    cin.ignore();

    cout << "\nNombre del curso: ";
    getline(cin, nombre);
    cout << "Codigo: ";
    getline(cin, codigo);
    cout << "Creditos: ";
    getline(cin, creditos);

    string query = "INSERT INTO cursos(nombre, codigo, creditos) VALUES('" +
                   nombre + "','" + codigo + "'," + creditos + ")";

    conexion.executeQuery(query);

    color(10);
    cout << "\nCurso agregado correctamente.\n";
    color(7);
}

void actualizar_curso(MySQLConexion &conexion) {
    string id, nombre, codigo, creditos;

    cout << "\nIngrese ID del curso a actualizar: ";
    cin >> id;
    cin.ignore();

    cout << "Nuevo nombre: ";
    getline(cin, nombre);
    cout << "Nuevo codigo: ";
    getline(cin, codigo);
    cout << "Nuevos creditos: ";
    getline(cin, creditos);

    string query = "UPDATE cursos SET nombre='" + nombre +
                   "', codigo='" + codigo +
                   "', creditos=" + creditos +
                   " WHERE id=" + id;

    conexion.executeQuery(query);

    color(14);
    cout << "\nCurso actualizado correctamente.\n";
    color(7);
}

void eliminar_curso(MySQLConexion &conexion) {
    string id;

    cout << "\nIngrese ID del curso a eliminar: ";
    cin >> id;

    conexion.executeQuery("DELETE FROM inscripciones WHERE curso_id=" + id);
    conexion.executeQuery("DELETE FROM cursos WHERE id=" + id);

    color(12);
    cout << "\nCurso eliminado correctamente.\n";
    color(7);
}

// ================= MAIN =================

int main() {
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

    vector<string> columnasEstudiantes = {"id", "nombre", "carnet", "edad", "correo"};
    vector<string> columnasCursos = {"id", "nombre", "codigo", "creditos"};

    EloquentORM estudiantes(conexion, "estudiantes", columnasEstudiantes);
    EloquentORM cursos(conexion, "cursos", columnasCursos);

    int opcion;

    do {
        color(11);
        cout << "\n===== SISTEMA DE ESTUDIANTES =====\n";
        color(7);

        cout << "1. Mostrar estudiantes\n";
        cout << "2. Agregar estudiante\n";
        cout << "3. Actualizar estudiante\n";
        cout << "4. Eliminar estudiante\n";
        cout << "5. Mostrar cursos\n";
        cout << "6. Agregar curso\n";
        cout << "7. Actualizar curso\n";
        cout << "8. Eliminar curso\n";
        cout << "9. Salir\n";

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
                mostrar_cursos(cursos);
                break;
            case 6:
                agregar_curso(conexion);
                break;
            case 7:
                actualizar_curso(conexion);
                break;
            case 8:
                eliminar_curso(conexion);
                break;
            case 9:
                color(14);
                cout << "\nSaliendo del sistema...\n";
                color(7);
                break;
            default:
                color(12);
                cout << "\nOpcion invalida.\n";
                color(7);
        }

    } while (opcion != 9);

    return 0;
}