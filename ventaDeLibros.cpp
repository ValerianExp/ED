#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <map>
#include <set>
#include <list>
#include <set>
#include <unordered_set>

//@ </answer>

using namespace std;

class ventaLibros
{
public:
    void nuevoLibro(int n, string x)
    {
        libros[x] += n;
    }

    void comprar(string x)
    {
        if (!libros.count(x))
        {
            throw std::invalid_argument("Libro no existente");
        }
        else if (libros.at(x) == 0)
        {
            throw std::out_of_range("No hay ejemplares");
        }
        if (librosVendidos.count(x))
        {
            int numVentas = librosVendidos.at(x).numVentas;
            auto it = librosVendidos.at(x).it;
            auto it2 = ventaLibros[numVentas + 1].begin();

            ventaLibros.at(numVentas).erase(it);
            librosVendidos.at(x).it = ventaLibros[numVentas + 1].insert(it2, x);
            librosVendidos.at(x).numVentas += 1;
        }
        else
        {
            auto it2 = ventaLibros[1].begin();
            librosVendidos[x] = {1, ventaLibros[1].insert(it2, x)};
        }
        libros.at(x) -= 1;
    }

    bool estaLibro(string x)
    {
        bool resultado = false;
        if (libros.count(x))
        {
            resultado = true;
        }
        return resultado;
    }

    void elimLibro(string x)
    {
        if (estaLibro(x))
        {
            if (librosVendidos.count(x))
            {
                auto it = librosVendidos.at(x).it;
                int numVentas = librosVendidos.at(x).numVentas;
                ventaLibros.at(numVentas).erase(it);
                librosVendidos.erase(x);
            }

            libros.erase(x);
        }
    }

    int numEjemplares(string x)
    {
        int resultado = 0;
        if (!estaLibro(x))
        {
            throw std::invalid_argument("Libro no existente");
        }
        resultado = libros.at(x);
        return resultado;
    }

    vector<string> top10()
    {
        vector<string> resultado;
        int cont = 0;

        for (auto i = ventaLibros.cbegin(); i != ventaLibros.cend() && cont < 10; ++i)
        {
            for (auto j = i->second.cbegin(); j != i->second.cend() && cont < 10; ++j)
            {
                resultado.push_back(*j);
                cont++;
            }
        }

        return resultado;
    }

private:
    struct infoLibro
    {
        int numVentas;
        list<string>::iterator it;
    };
    // numero de ventas -> lista libros con estas ventas
    map<int, list<string>, greater<int>> ventaLibros;

    // Nombre libro -> cantidadLibros
    unordered_map<string, int> libros;

    // Nombre libro -> infoLibro
    unordered_map<string, infoLibro> librosVendidos;
};

//---------------------------------------------------------------
// No modificar nada por debajo de esta línea
// -------------------------------------------------------------
//@ </answer>

bool tratar_caso()
{
    ventaLibros l;
    int num;
    cin >> num;
    if (cin.eof())
        return false;

    string operacion;

    while (num > 0)
    {
        try
        {
            cin >> operacion;
            if (operacion == "nuevoLibro")
            {
                int n;
                string x;
                cin >> n;

                char c;
                cin.get(c);

                getline(cin, x);
                l.nuevoLibro(n, x);
            }
            else if (operacion == "comprar")
            {
                string x;
                char c;
                cin.get(c);

                getline(cin, x);
                l.comprar(x);
            }
            else if (operacion == "estaLibro")
            {
                string x;
                char c;
                cin.get(c);

                getline(cin, x);
                bool esta = l.estaLibro(x);
                if (esta)
                {
                    cout << "El libro " << x << " esta en el sistema" << endl;
                }
                else
                {
                    cout << "No existe el libro " << x << " en el sistema" << endl;
                }
            }
            else if (operacion == "numEjemplares")
            {
                string x;
                int n;

                char c;
                cin.get(c);

                getline(cin, x);

                if (l.estaLibro(x))
                {
                    n = l.numEjemplares(x);
                    cout << "Existen " << n << " ejemplares del libro " << x << endl;
                }
                else
                {
                    cout << "No existe el libro " << x << " en el sistema" << endl;
                }
            }
            else if (operacion == "elimLibro")
            {
                string x;

                char c;
                cin.get(c);

                getline(cin, x);
                l.elimLibro(x);
            }
            else if (operacion == "top10")
            {
                vector<string> top10;
                top10 = l.top10();
                cout << "TOP10" << endl;
                for (auto &i : top10)
                {
                    cout << "    " << i << endl;
                }
            }
        }
        catch (invalid_argument &e)
        {
            cout << e.what() << "\n";
        }
        catch (out_of_range &e)
        {
            cout << e.what() << "\n";
        }
        catch (exception &e)
        {
            cout << e.what() << "\n";
        }
        num--;
    }
    cout << "---\n";
    return true;
}

int main()
{
#ifndef DOMJUDGE
    std::ifstream in("samples\\ventaDeLibros_sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso())
    {
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif
    return 0;
}