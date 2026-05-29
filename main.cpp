#include <iostream>
#include <vector>
#include <map>
#include <windows.h>

#include "MySQLConexion.h"
#include "EloquentORM.h"

using namespace std;

// ================= CLASE CONSOLA =================

class Consola {
public:
    static void color(int c) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    }
};

// ================= CLASE ESTUDIANTES =================

class Estudiantes {
private:
    MySQLConexion &conexion;
    EloquentORM orm;

public:
    Estudiantes(MySQLConexion &conexion)
        : conexion(conexion),
          orm(conexion, "estudiantes", {"id", "nombre", "carnet", "edad", "correo"}) {}

    void mostrar() {
        auto lista = orm.getAll();

        Consola::color(11);
        cout << "\n===== LISTA DE ESTUDIANTES =====\n";
        Consola::color(7);

        for (auto &reg : lista) {
            cout << "ID: " << reg["id"]
                 << " | Nombre: " << reg["nombre"]
                 << " | Carnet: " << reg["carnet"]
                 << " | Edad: " << reg["edad"]
                 << " | Correo: " << reg["correo"] << endl;
        }
    }

    void agregar() {
        string nombre, carnet, correo;
        int edad;

        cin.ignore();

        cout << "\nNombre: ";
        getline(cin, nombre);
        cout << "Carnet: ";
        getline(cin, carnet);
        cout << "Edad: ";
        cin >> edad;
        cin.ignore();
        cout << "Correo: ";
        getline(cin, correo);

        string sql = "INSERT INTO estudiantes(nombre, carnet, edad, correo) VALUES ('" +
                     nombre + "', '" + carnet + "', " + to_string(edad) + ", '" + correo + "')";

        conexion.executeQuery(sql);

        Consola::color(10);
        cout << "\nEstudiante agregado correctamente.\n";
        Consola::color(7);
    }

    void actualizar() {
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

        Consola::color(14);
        cout << "\nEstudiante actualizado correctamente.\n";
        Consola::color(7);
    }

    void eliminar() {
        string id;

        cout << "\nIngrese ID del estudiante a eliminar: ";
        cin >> id;

        conexion.executeQuery("DELETE FROM inscripciones WHERE estudiante_id=" + id);
        conexion.executeQuery("DELETE FROM estudiantes WHERE id=" + id);

        Consola::color(12);
        cout << "\nEstudiante eliminado correctamente.\n";
        Consola::color(7);
    }

    void menu() {
        int opcion;

        do {
            Consola::color(11);
            cout << "\n===== GESTION DE ESTUDIANTES =====\n";
            Consola::color(7);

            cout << "1. Mostrar estudiantes\n";
            cout << "2. Agregar estudiante\n";
            cout << "3. Actualizar estudiante\n";
            cout << "4. Eliminar estudiante\n";
            cout << "5. Regresar\n";
            cout << "\nSeleccione una opcion: ";
            cin >> opcion;

            switch (opcion) {
                case 1: mostrar(); break;
                case 2: agregar(); break;
                case 3: actualizar(); break;
                case 4: eliminar(); break;
                case 5: break;
                default:
                    Consola::color(12);
                    cout << "\nOpcion invalida.\n";
                    Consola::color(7);
            }

        } while (opcion != 5);
    }
};

// ================= CLASE CURSOS =================

class Cursos {
private:
    MySQLConexion &conexion;
    EloquentORM orm;

public:
    Cursos(MySQLConexion &conexion)
        : conexion(conexion),
          orm(conexion, "cursos", {"id", "nombre", "codigo", "creditos"}) {}

    void mostrar() {
        auto lista = orm.getAll();

        Consola::color(11);
        cout << "\n===== LISTA DE CURSOS =====\n";
        Consola::color(7);

        for (auto &reg : lista) {
            cout << "ID: " << reg["id"]
                 << " | Nombre: " << reg["nombre"]
                 << " | Codigo: " << reg["codigo"]
                 << " | Creditos: " << reg["creditos"] << endl;
        }
    }

    void agregar() {
        string nombre, codigo;
        int creditos;

        cin.ignore();

        cout << "\nNombre del curso: ";
        getline(cin, nombre);
        cout << "Codigo: ";
        getline(cin, codigo);
        cout << "Creditos: ";
        cin >> creditos;

        string sql = "INSERT INTO cursos(nombre, codigo, creditos) VALUES('" +
                     nombre + "','" + codigo + "'," + to_string(creditos) + ")";

        conexion.executeQuery(sql);

        Consola::color(10);
        cout << "\nCurso agregado correctamente.\n";
        Consola::color(7);
    }

    void actualizar() {
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

        string sql = "UPDATE cursos SET nombre='" + nombre +
                     "', codigo='" + codigo +
                     "', creditos=" + creditos +
                     " WHERE id=" + id;

        conexion.executeQuery(sql);

        Consola::color(14);
        cout << "\nCurso actualizado correctamente.\n";
        Consola::color(7);
    }

    void eliminar() {
        string id;

        cout << "\nIngrese ID del curso a eliminar: ";
        cin >> id;

        conexion.executeQuery("DELETE FROM inscripciones WHERE curso_id=" + id);
        conexion.executeQuery("DELETE FROM cursos WHERE id=" + id);

        Consola::color(12);
        cout << "\nCurso eliminado correctamente.\n";
        Consola::color(7);
    }

    void menu() {
        int opcion;

        do {
            Consola::color(11);
            cout << "\n===== GESTION DE CURSOS =====\n";
            Consola::color(7);

            cout << "1. Mostrar cursos\n";
            cout << "2. Agregar curso\n";
            cout << "3. Actualizar curso\n";
            cout << "4. Eliminar curso\n";
            cout << "5. Regresar\n";
            cout << "\nSeleccione una opcion: ";
            cin >> opcion;

            switch (opcion) {
                case 1: mostrar(); break;
                case 2: agregar(); break;
                case 3: actualizar(); break;
                case 4: eliminar(); break;
                case 5: break;
                default:
                    Consola::color(12);
                    cout << "\nOpcion invalida.\n";
                    Consola::color(7);
            }

        } while (opcion != 5);
    }
};

// ================= CLASE ASIGNATURAS =================
// Esta clase administra la asignacion de estudiantes a cursos.
// En la base de datos corresponde a la tabla inscripciones.

class Asignaturas {
private:
    MySQLConexion &conexion;

public:
    Asignaturas(MySQLConexion &conexion) : conexion(conexion) {}

    void mostrar() {
        string sql =
            "SELECT inscripciones.id, estudiantes.nombre, cursos.nombre, "
            "inscripciones.fecha_inscripcion, inscripciones.estado "
            "FROM inscripciones "
            "INNER JOIN estudiantes ON inscripciones.estudiante_id = estudiantes.id "
            "INNER JOIN cursos ON inscripciones.curso_id = cursos.id";

        conexion.executeQuery(sql);

        MYSQL_RES* resultado = mysql_store_result(conexion.getConnection());
        MYSQL_ROW fila;

        Consola::color(11);
        cout << "\n===== LISTA DE ASIGNATURAS =====\n";
        Consola::color(7);

        while ((fila = mysql_fetch_row(resultado))) {
            cout << "ID: " << fila[0]
                 << " | Estudiante: " << fila[1]
                 << " | Curso: " << fila[2]
                 << " | Fecha: " << fila[3]
                 << " | Estado: " << fila[4] << endl;
        }

        mysql_free_result(resultado);
    }

    void agregar() {
        int estudianteId, cursoId;
        string fecha, estado;

        cout << "\nID del estudiante: ";
        cin >> estudianteId;

        cout << "ID del curso: ";
        cin >> cursoId;

        cin.ignore();

        cout << "Fecha YYYY-MM-DD: ";
        getline(cin, fecha);

        cout << "Estado: ";
        getline(cin, estado);

        string sql =
            "INSERT INTO inscripciones(estudiante_id, curso_id, fecha_inscripcion, estado) VALUES(" +
            to_string(estudianteId) + ", " +
            to_string(cursoId) + ", '" +
            fecha + "', '" +
            estado + "')";

        conexion.executeQuery(sql);

        Consola::color(10);
        cout << "\nAsignatura agregada correctamente.\n";
        Consola::color(7);
    }

    void eliminar() {
        string id;

        cout << "\nIngrese ID de la asignatura a eliminar: ";
        cin >> id;

        conexion.executeQuery("DELETE FROM inscripciones WHERE id=" + id);

        Consola::color(12);
        cout << "\nAsignatura eliminada correctamente.\n";
        Consola::color(7);
    }

    void menu() {
        int opcion;

        do {
            Consola::color(11);
            cout << "\n===== GESTION DE ASIGNATURAS =====\n";
            Consola::color(7);

            cout << "1. Mostrar asignaturas\n";
            cout << "2. Agregar asignatura\n";
            cout << "3. Eliminar asignatura\n";
            cout << "4. Regresar\n";
            cout << "\nSeleccione una opcion: ";
            cin >> opcion;

            switch (opcion) {
                case 1: mostrar(); break;
                case 2: agregar(); break;
                case 3: eliminar(); break;
                case 4: break;
                default:
                    Consola::color(12);
                    cout << "\nOpcion invalida.\n";
                    Consola::color(7);
            }

        } while (opcion != 4);
    }
};

// ================= CLASE SISTEMA UNIVERSITARIO =================

class SistemaUniversitario {
private:
    MySQLConexion conexion;
    Estudiantes *estudiantes;
    Cursos *cursos;
    Asignaturas *asignaturas;

public:
    SistemaUniversitario()
        : conexion(
            "root",
            "Maynor1234",
            "proyecto_estudiantes",
            "127.0.0.1",
            3306
          )
    {
        estudiantes = nullptr;
        cursos = nullptr;
        asignaturas = nullptr;
    }

    bool iniciar() {
        if (!conexion.open()) {
            Consola::color(12);
            cerr << "Error al conectar con MySQL" << endl;
            Consola::color(7);
            return false;
        }

        Consola::color(10);
        cout << "Conexion exitosa a MySQL\n";
        Consola::color(7);

        estudiantes = new Estudiantes(conexion);
        cursos = new Cursos(conexion);
        asignaturas = new Asignaturas(conexion);

        return true;
    }

    void menu_principal() {
        int opcion;

        do {
            Consola::color(11);
            cout << "\n===== SISTEMA UNIVERSITARIO =====\n";
            Consola::color(7);

            cout << "1. Gestionar estudiantes\n";
            cout << "2. Gestionar cursos\n";
            cout << "3. Gestionar asignaturas\n";
            cout << "4. Salir\n";
            cout << "\nSeleccione una opcion: ";
            cin >> opcion;

            switch (opcion) {
                case 1: estudiantes->menu(); break;
                case 2: cursos->menu(); break;
                case 3: asignaturas->menu(); break;
                case 4:
                    Consola::color(14);
                    cout << "\nSaliendo del sistema...\n";
                    Consola::color(7);
                    break;
                default:
                    Consola::color(12);
                    cout << "\nOpcion invalida.\n";
                    Consola::color(7);
            }

        } while (opcion != 4);
    }

    ~SistemaUniversitario() {
        delete estudiantes;
        delete cursos;
        delete asignaturas;
    }
};

// ================= MAIN =================

int main() {
    SistemaUniversitario sistema;

    if (!sistema.iniciar()) {
        return 1;
    }

    sistema.menu_principal();

    return 0;
}