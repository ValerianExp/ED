#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <list>

using namespace std;

class Elecciones
{
public:
    void nuevo_paciente(const string &p, int g)
    {
        if (pacientes.count(p))
        {
            throw std::domain_error("Paciente repetido");
        }
        if (!(g >= 1 && g <= 3))
        {
            throw std::domain_error("Gravedad incorrecta");
        }
        auto it = gravedad[g].insert(gravedad[g].begin(), p);
        pacientes[p] = {g, it};
    }

    int gravedad_actual(const string &p)
    {
        if (!pacientes.count(p))
        {
            throw std::domain_error("Paciente inexistente");
        }
        return pacientes.at(p).gravedad;
    }

    string siguiente()
    {
        string s;
        bool ok = false;
        int g = 0;
        if (gravedad.count(3) && !gravedad.at(3).empty())
        {
            g = 3;
            ok = true;
        }
        else if (!ok && gravedad.count(2) && !gravedad.at(2).empty())
        {
            g = 2;
            ok = true;
        }
        else if (!ok && gravedad.count(1) && !gravedad.at(1).empty())
        {
            g = 1;
        }
        else
        {
            throw std::domain_error("No hay pacientes");
        }
        s = gravedad.at(g).back();
        auto it = pacientes.at(s).it;
        gravedad.at(g).erase(it);
        pacientes.erase(s);
        return s;
    }

    void mejora(const string &p)
    {
        if (!pacientes.count(p))
        {
            throw std::domain_error("Paciente inexistente");
        }
        int g = pacientes.at(p).gravedad;
        auto it = pacientes.at(p).it;
        gravedad.at(g).erase(it);
        pacientes.at(p).gravedad = g - 1;
        if (pacientes.at(p).gravedad == 0)
        {
            pacientes.erase(p);
            pacientesRecuperados.insert(p);
        }
        else
        {
            auto it2 = gravedad[g - 1].insert(gravedad[g - 1].end(), p);
            pacientes.at(p).it = it2;
        }
    }

    vector<string> recuperados()
    {
        vector<string> resultado;
        for (auto i : pacientesRecuperados)
        {
            resultado.push_back(i);
        }
        // sort(resultado.begin(), resultado.end());
        return resultado;
    }

private:
    struct infoPaciente
    {
        int gravedad;
        list<string>::iterator it;
    };
    // gravedad -> lista de pacientes
    map<int, list<string>, greater<int>> gravedad;
    unordered_map<string, infoPaciente> pacientes;
    set<string> pacientesRecuperados;
};

bool tratar_caso()
{
    string comando;
    cin >> comando;
    if (!cin)
    {
        return false;
    }

    Elecciones urgencias;

    while (comando != "FIN")
    {
        try
        {
            if (comando == "nuevo_paciente")
            {
                string p;
                int g;
                cin >> p;
                cin >> g;
                urgencias.nuevo_paciente(p, g);
            }
            else if (comando == "mejora")
            {
                string p;
                cin >> p;
                urgencias.mejora(p);
            }
            else if (comando == "siguiente")
            {
                string p;
                p = urgencias.siguiente();
                cout << "Siguiente paciente: " << p << endl;
            }
            else if (comando == "gravedad_actual")
            {
                string p;
                int g;
                cin >> p;
                g = urgencias.gravedad_actual(p);
                cout << "La gravedad de " << p << " es " << g << endl;
            }
            else if (comando == "recuperados")
            {
                vector<string> recuperados;
                recuperados = urgencias.recuperados();
                cout << "Lista de recuperados: ";
                for (auto i : recuperados)
                {
                    cout << i << " ";
                }
                cout << endl;
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
    std::ifstream in("samples\\urgencias_sample.in");
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