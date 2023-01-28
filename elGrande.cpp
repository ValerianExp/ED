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
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <set>
#include <list>
#include <unordered_set>
#include <map>
// añade las librerías de la STL que necesites

using namespace std;

// Elige el tipo representante adecuado para el TAD ElGrande e
// implementa sus operaciones. Puedes añadir métodos o funciones privadas
// si lo consideras conveniente. Justifica la elección de los tipos y el
// coste de las operaciones.
//@ <answer>

using jugador = string;
using region = string;

class ElGrande
{

public:
    void anyadir_jugador(const jugador &j)
    {
        if (jugadores.count(j))
        {
            throw std::domain_error("Jugador ya existente");
        }
        infoJugador ij;
        jugadores[j] = ij;
    }

    void colocar_caballero(const jugador &j, const region &r)
    {
        if (!jugadores.count(j))
        {
            throw std::domain_error("Jugador no existente");
        }
        infoRegion &ir = regiones[r];

        regiones.at(r).caballeros[j] += 1;
        if (regiones.at(r).caballeros.at(j) > regiones.at(r).num_caballeros_ganador)
        {
            string antiguo_ganador = ir.ganador;
            ir.num_caballeros_ganador = regiones.at(r).caballeros[j];
            ir.ganador = j;
            ir.enDisputa = false;
            if (antiguo_ganador != "")
            {
                jugadores[antiguo_ganador].puntos -= 1;
                if (jugadores[antiguo_ganador].puntos == 0)
                {
                    regiones.at(r).caballeros.erase(antiguo_ganador);
                }
            }
            jugadores[j].puntos += 1;
        }
        else if (regiones.at(r).caballeros.at(j) == regiones.at(r).num_caballeros_ganador)
        {
            if (ir.ganador != "")
            {
                jugadores.at(ir.ganador).puntos -= 1;
                ir.ganador = "";
            }
            ir.num_caballeros_ganador = regiones.at(r).caballeros.at(j);
        }
        if (regiones.at(r).caballeros.size() > 1)
        {
            regiones.at(r).enDisputa = true;
        }
    }

    int puntuacion(const jugador &j) const
    {
        if (!jugadores.count(j))
        {
            throw std::domain_error("Jugador no existente");
        }

        return jugadores.at(j).puntos;
    }

    vector<region> regiones_en_disputa() const
    {
        vector<string> resultado;
        for (auto &r : regiones)
        {
            if (r.second.enDisputa)
            {
                resultado.push_back(r.first);
            }
        }
        sort(resultado.begin(), resultado.end());
        return resultado;
    }

    void expulsar_caballeros(const region &r)
    {
        if (!regiones.count(r) || regiones.at(r).caballeros.empty())
        {
            throw std::domain_error("Region vacia");
        }
        infoRegion ir = regiones.at(r);
        jugadores.at(ir.ganador).puntos -= 1;
        infoRegion aux;
        regiones.at(r) = aux;
    }

private:
    struct infoRegion
    {
        bool enDisputa;
        // Jugadores -> num_caballeros en esa region
        unordered_map<string, int> caballeros;

        string ganador;
        int num_caballeros_ganador;

        infoRegion() : enDisputa(false), ganador(""), num_caballeros_ganador(0) {}
    };

    unordered_map<string, infoRegion> regiones;

    struct infoJugador
    {
        int puntos;
        infoJugador() : puntos(0) {}
    };

    unordered_map<string, infoJugador> jugadores;
};

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso()
{
    string orden, jug, reg;
    cin >> orden;
    if (!cin)
        return false;

    ElGrande juego;

    while (orden != "FIN")
    {
        try
        {
            if (orden == "anyadir_jugador")
            {
                cin >> jug;
                juego.anyadir_jugador(jug);
            }
            else if (orden == "colocar_caballero")
            {
                cin >> jug >> reg;
                juego.colocar_caballero(jug, reg);
            }
            else if (orden == "puntuacion")
            {
                cin >> jug;
                auto puntos = juego.puntuacion(jug);
                cout << "Puntuacion de " << jug << ": " << puntos << '\n';
            }
            else if (orden == "regiones_en_disputa")
            {
                auto regs = juego.regiones_en_disputa();
                cout << "Regiones en disputa:\n";
                for (auto const &r : regs)
                {
                    cout << r << '\n';
                }
            }
            else if (orden == "expulsar_caballeros")
            {
                cin >> reg;
                juego.expulsar_caballeros(reg);
            }
        }
        catch (domain_error &e)
        {
            cout << "ERROR: " << e.what() << '\n';
        }
        cin >> orden;
    }
    cout << "---\n";
    return true;
}

int main()
{
#ifndef DOMJUDGE
    std::ifstream in("samples\\elGrande_sample.in");
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
