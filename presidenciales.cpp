#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <list>

using namespace std;

class Elecciones
{
public:
    void nuevos_estados(const string &nombre, int num_compromisarios)
    {
        if (estados.count(nombre))
        {
            throw std::domain_error("Estado ya existente");
        }
        estados[nombre].num_compromisarios = num_compromisarios;
    }

    void sumar_votos(const string &estado, const string &partido, int num_votos)
    {
        if (!estados.count(estado))
        {
            throw std::domain_error("Estado no encontrado");
        }
        auto e = estados.at(estado);
        e.votos[partido] += num_votos;

        string antiguoGanador = e.ganador;
        if (e.votos.at(partido) > e.num_votos_ganador)
        {
            e.num_votos_ganador = e.votos.at(partido);
            e.ganador = partido;

        }
    }

    string ganador_en(const string &estado) const {}        

    vector<pair<string, int>> resultados() const
    {
    }

private:
    struct InfoEstado
    {
        int num_compromisarios;
        // partidos -> votos
        unordered_map<string, int> votos;

        string ganador;
        int num_votos_ganador;

        InfoEstado(int num_compromisarios) : num_compromisarios(num_compromisarios), ganador(""), num_votos_ganador(0) {}
    };
    // estado -> InfoEstado
    unordered_map<string, InfoEstado> estados;

    // partidos -> num_compromisarios_totales
    map<string, int> partidos;
};

bool tratar_caso()
{
    string comando;
    cin >> comando;
    if (!cin)
    {
        return false;
    }

    // AutoEscuela escuela;

    while (comando != "FIN")
    {
        try
        {
            if (comando == "")
            {
            }
            else if (comando == "")
            {
            }
            else if (comando == "")
            {
            }
            else if (comando == "")
            {
            }
            else if (comando == "")
            {
            }
            else if (comando == "")
            {
            }
        }
        catch (std::exception &e)
        {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        cin >> comando;
    }
    cout << "---" << endl;
    return true;
}

int main()
{
#ifndef DOMJUDGE
    std::ifstream in("samples\\sample.in");
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