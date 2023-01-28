#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class AutoEscuela {
public:
    void alta(const string& alumno, const string& profesor) {
        if (alumnos.count(alumno)) {
            InfoAlumno iA = alumnos.at(alumno);
            profesores.at(iA.profesor).erase(alumno);
        }

        alumnos[alumno].profesor = profesor;
        profesores[profesor].insert(alumno);
    }

    bool es_alumno(const string& alumno, const string& profesor) const {
        //return profesores.count(profesor) && //profesores[profesor].count(alumno); El [] no es una operacion const el at(), sí
            //profesores.at(profesor).count(alumno); //O(log tamaño de alumnos)

        return alumnos.count(alumno) && alumnos.at(alumno).profesor == profesor; //O(1)
    }

    int puntuacion(const string& alumno) const {
        return buscar_alumno(alumno).puntuacion;
    }


    void actualizar(const string& alumno, int puntos) {
        buscar_alumno(alumno).puntuacion += puntos;
    }

    vector<string> examen(const string& profesor, int minimo_puntos) const {
        vector<string> result;

        if (!profesores.count(profesor)) {
            return result;
        }
        set<string> s = profesores.at(profesor);
        for (auto i : s) {
            InfoAlumno aux = buscar_alumno(i);
            if (aux.puntuacion >= minimo_puntos) {
                result.push_back(i);
            }
        }
        return result;
    }

    void aprobar(const string& alumno) {
        InfoAlumno& info = buscar_alumno(alumno);
        profesores.at(info.profesor).erase(alumno);
        alumnos.erase(alumno);
    }

private:
    struct InfoAlumno {
        string profesor;
        int puntuacion;

        //Constructor por defecto del struct infoAlumno
        InfoAlumno() : profesor(""), puntuacion(0) {}
    };

    //profesor -> conjunto de alumnos
    unordered_map<string, set<string>> profesores;

    //alumno -> {profesor, puntuacion}
    unordered_map<string, InfoAlumno> alumnos;

    //Version no constante
    InfoAlumno& buscar_alumno(const string& nombre) {
        auto it = alumnos.find(nombre);
        if (it == alumnos.end()) {
            throw std::domain_error("El alumno " + nombre + " no esta matriculado");
        }

        return it->second;
    }
    //Version constante
    //Un metodo constante si devuelve un referencia tiene que ser un referencia constante
    const InfoAlumno& buscar_alumno(const string& nombre) const {
        auto it = alumnos.find(nombre);
        if (it == alumnos.end()) {
            throw std::domain_error("El alumno " + nombre + " no esta matriculado");
        }

        return it->second;
    }

};

bool tratar_caso() {
    string comando;
    cin >> comando;
    if (!cin) {
        return false;
    }

    AutoEscuela escuela;

    while (comando != "FIN") {
        try {
            if (comando == "alta") {
                string alumno, profesor;
                cin >> alumno;
                cin >> profesor;
                escuela.alta(alumno, profesor);
            }
            else if (comando == "es_alumno") {
                string alumno, profesor;
                cin >> alumno;
                cin >> profesor;
                if (escuela.es_alumno(alumno, profesor)) {
                    cout << alumno << " es alumno de " << profesor << endl;
                }
                else {
                    cout << alumno << " no es alumno de " << profesor << endl;
                }
            }
            else if (comando == "examen") {
                string profesor;
                int puntuacion;
                cin >> profesor;
                cin >> puntuacion;
                auto listado = escuela.examen(profesor, puntuacion);
                cout << "Alumnos de " << profesor << " a examen:" << endl;
                for (auto alumno : listado) {
                    cout << alumno << endl;
                }
            }
            else if (comando == "actualizar") {
                string alumno;
                int puntuacion;
                cin >> alumno;
                cin >> puntuacion;
                escuela.actualizar(alumno, puntuacion);
            }
            else if (comando == "aprobar") {
                string alumno;
                cin >> alumno;
                escuela.aprobar(alumno);
            }
            else if (comando == "puntuacion") {
                string alumno;
                cin >> alumno;
                int puntuacion = escuela.puntuacion(alumno);
                cout << "Puntuacion de " << alumno << ": " << puntuacion << endl;
            }
        }
        catch (std::exception e) {
            std::cout << "ERROR" << '\n';
        }
        cin >> comando;

    }
    cout << "---" << endl;
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("samples\\autoescuela_sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso())
        ;

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se necesita
    // system("PAUSE");
#endif
    return 0;
}