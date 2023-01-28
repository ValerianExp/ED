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
    // Metodos
private:
    // Tads
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