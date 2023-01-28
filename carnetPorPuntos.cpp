#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <list>

using namespace std;

class Carnet
{
public:
    void nuevo(const string &dni)
    {
        if (conductores.count(dni))
        {
            throw std::domain_error("Conductor duplicado");
        }
        // InfoConductor info;
        // conductores[dni] = info;
        // // puntosConductores[info.puntos].insert(dni);
        // puntosConductores[info.puntos].push_front(dni);
        // info.it = puntosConductores[info.puntos].begin();
        // conductores[dni].it = puntosConductores[info.puntos].begin();

        InfoConductor info;
        puntosConductores[info.puntos].push_front(dni);
        conductores[dni] = info;
        conductores[dni].it = puntosConductores.at(info.puntos).begin();
    }

    void quitar(const string &dni, int puntos)
    {
        InfoConductor &conductor = buscar_conductor(dni);
        // puntosConductores[conductor.puntos].erase(dni);
        puntosConductores[conductor.puntos].erase(conductor.it);
        conductor.puntos -= puntos;
        if (conductor.puntos <= 0)
        {
            conductor.puntos = 0;
        }
        // puntosConductores[conductor.puntos].insert(dni);
        puntosConductores[conductor.puntos].push_front(dni);
        conductores[dni].it = puntosConductores[conductor.puntos].begin();
    }

    int consultar(const string &dni) const
    {
        return buscar_conductor(dni).puntos;
    }

    int cuantos_con_puntos(int puntos)
    {
        if (puntos < 0 || puntos > 15)
        {
            throw std::domain_error("Puntos no validos");
        }

        // for (auto conductor : conductores) {
        //     if (conductor.second.puntos == puntos) {
        //         resultado++;
        //     }
        // }
        int result;
        if (!puntosConductores.count(puntos))
        {
            result = 0;
        }
        else
        {
            result = puntosConductores.at(puntos).size();
        }

        return result;
    }

private:
    struct InfoConductor
    {
        int puntos;
        list<string>::iterator it;
        InfoConductor() : puntos(15) {}
    };

    // dni -> puntos
    unordered_map<string, InfoConductor> conductores;

    // puntos -> lista de conductores
    unordered_map<int, list<string>> puntosConductores;

    // Version no constante
    InfoConductor &buscar_conductor(const string &dni)
    {
        auto it = conductores.find(dni);
        if (!conductores.count(dni))
        {
            throw std::domain_error("Conductor inexistente");
        }
        return it->second;
    }

    // Version constante
    const InfoConductor &buscar_conductor(const string &dni) const
    {
        auto it = conductores.find(dni);
        if (!conductores.count(dni))
        {
            throw std::domain_error("Conductor inexistente");
        }
        return it->second;
    }
};

bool tratar_caso()
{
    string comando;
    cin >> comando;
    if (!cin)
    {
        return false;
    }

    Carnet c;

    while (comando != "FIN")
    {
        try
        {
            if (comando == "nuevo")
            {
                string dni;
                cin >> dni;
                c.nuevo(dni);
            }
            else if (comando == "cuantos_con_puntos")
            {
                int puntos;
                cin >> puntos;
                int cont = c.cuantos_con_puntos(puntos);
                cout << "Con " << puntos << " puntos hay " << cont << endl;
            }
            else if (comando == "quitar")
            {
                string dni;
                int puntos;
                cin >> dni;
                cin >> puntos;
                c.quitar(dni, puntos);
            }
            else if (comando == "consultar")
            {
                string dni;
                int puntos;
                cin >> dni;
                puntos = c.consultar(dni);
                cout << "Puntos de " << dni << ": " << puntos << endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "ERROR: " << e.what() << endl;
        }
        cin >> comando;
    }
    cout << "---" << endl;

    return true;
}

int main()
{
#ifndef DOMJUDGE
    std::ifstream in("samples\\carnetPorPuntos_sample.in");
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