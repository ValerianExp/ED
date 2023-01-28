#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <list>

using namespace std;

class empleo
{
public:
    void altaOficina(const string &p, const string &e)
    {
        if (!personas[p].count(e))
        {
            auto it = empleos[e].insert(empleos[e].begin(), p);
            personas[p].insert({e, it});
        }
    }

    string ofertaEmpleo(const string &e)
    {
        if (!empleos.count(e))
        {
            throw std::domain_error("No existen personas apuntadas a este empleo");
        }

        string nombre;
        nombre = empleos.at(e).back();
        if (personas.count(nombre))
        {
            auto empleosPersona = personas.at(nombre);

            for (auto i : empleosPersona)
            {
                empleos.at(i.first).erase(i.second);
                if (empleos.at(i.first).size() == 0)
                {
                    empleos.erase(i.first);
                }
            }

            personas.erase(nombre);
        }

        return nombre;
    }

    vector<string> listadoEmpleos(const string &p)
    {
        if (!personas.count(p))
        {
            throw std::domain_error("Persona inexistente");
        }

        vector<string> resultado;
        for (auto i : personas.at(p))
        {
            resultado.push_back(i.first);
        }
        return resultado;
    }

private:
    unordered_map<string, list<string>> empleos;
    unordered_map<string, map<string, list<string>::iterator>> personas;
};

bool tratar_caso()
{
    string comando;
    cin >> comando;
    if (!cin)
    {
        return false;
    }

    empleo e;

    while (comando != "FIN")
    {
        try
        {
            if (comando == "altaOficina")
            {
                string persona;
                string empleo;
                cin >> persona;
                cin >> empleo;
                e.altaOficina(persona, empleo);
            }
            else if (comando == "ofertaEmpleo")
            {
                string empleo;
                string persona;
                cin >> empleo;
                persona = e.ofertaEmpleo(empleo);
                cout << empleo << ": " << persona << endl;
            }
            else if (comando == "listadoEmpleos")
            {
                vector<string> listado;
                string persona;
                cin >> persona;
                listado = e.listadoEmpleos(persona);
                cout << persona << ": ";
                for (auto a : listado)
                {
                    cout << a << " ";
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
    std::ifstream in("samples\\empleo_sample.in");
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