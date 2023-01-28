/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo puedes
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>.
  *
  * Tampoco está permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  // Nombre y Apellidos:
  //@ </answer>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>
// añade las librerías de la STL que necesites

using namespace std;

// Elige el tipo representante adecuado para el TAD ElGrande e
// implementa sus operaciones. Puedes añadir métodos o funciones privadas
// si lo consideras conveniente. Justifica la elección de los tipos y el
// coste de las operaciones.
//@ <answer>

using jugador = string;
using region = string;

class ElGrande {
public:
    void anyadir_jugador(const jugador& j) {
        if (jugadores.count(j)) {
            throw std::domain_error("Jugador existente");
        }

        jugadores.insert({ j, 0 });
    }

    void colocar_caballero(const jugador& j, const region& r) {
        if (!jugadores.count(j)) {
            throw std::domain_error("Jugador no existente");
        }
        // int antiguo_valor = regiones[r].at(j);
        // regiones[r].insert({j, antiguo_valor + 1});
    }

    int puntuacion(const jugador& j) const {
        return 0;
    }

    vector<region> regiones_en_disputa() const {

        return { "a" };
    }

    void expulsar_caballeros(const region& r) {}

private:
    // jugador, puntuacion
    InfoAlumno<string, int> jugadores;
    // jugador, region
    // unordered_map<string, string> caballeros;
    // (nombreRegion, (jugadores que tienen al menos un caballero))
    InfoAlumno<string, unordered_set<string>> regiones;
};

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    string orden, jug, reg;
    cin >> orden;
    if (!cin)
        return false;

    ElGrande juego;

    while (orden != "FIN") {
        try {
            if (orden == "anyadir_jugador") {
                cin >> jug;
                juego.anyadir_jugador(jug);
            }
            else if (orden == "colocar_caballero") {
                cin >> jug >> reg;
                juego.colocar_caballero(jug, reg);
            }
            else if (orden == "puntuacion") {
                cin >> jug;
                auto puntos = juego.puntuacion(jug);
                cout << "Puntuacion de " << jug << ": " << puntos << '\n';
            }
            else if (orden == "regiones_en_disputa") {
                auto regs = juego.regiones_en_disputa();
                cout << "Regiones en disputa:\n";
                for (auto const& r : regs) {
                    cout << r << '\n';
                }
            }
            else if (orden == "expulsar_caballeros") {
                cin >> reg;
                juego.expulsar_caballeros(reg);
            }
        }
        catch (domain_error& e) {
            cout << "ERROR: " << e.what() << '\n';
        }
        cin >> orden;
    }
    cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos3.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso())
        ;

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se necesita
    // system("PAUSE");
#endif
    return 0;
}
